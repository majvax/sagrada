#include "bot.h"
#include "time.h"
#include "unistd.h"

#define DBG_PRINT(fmt, ...)                                            \
    do {                                                               \
        time_t t = time(NULL);                                         \
        printf("[%s:%d] "fmt"\n",__FILE__, __LINE__, ##__VA_ARGS__);   \
        while(time(NULL) - t < 5);                                     \
    } while(0)


void random_move(struct board* b, struct die** dice, int* dice_left) {
    int die_indices[5];
    int num_dice = 0;

    for (int i = 0; i < 5; i++) {
        if (dice[i] != NULL) {
            die_indices[num_dice++] = i;
        }
    }

    if (num_dice == 0)
        return;

    int die_index = die_indices[rand() % num_dice];
    struct die* d = dice[die_index];

    int empty_positions[ROW * COLUMN][2];
    int num_positions = 0;

    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COLUMN; y++) {
            if (placeable(b, d, x, y)) {
                empty_positions[num_positions][0] = x;
                empty_positions[num_positions][1] = y;
                num_positions++;
            }
        }
    }

    if (num_positions == 0)
        return;

    int pos_index = rand() % num_positions;
    int x = empty_positions[pos_index][0];
    int y = empty_positions[pos_index][1];

    place_die(b, d, x, y);
    free_die(dice[die_index]);
    dice[die_index] = NULL;
    (*dice_left)--;
}

int simulate_game(struct board* bot_board, struct board* opp_board, struct die** dice_set,
                   int rounds_remaining, int priority) {
    for (int r = 0; r < rounds_remaining; ++r) {
        struct die** dice = get_dice(dice_set, 5);
        if (dice == NULL)
            return 0;
        int dice_left = 5;

        if (!priority) {
            // Bot has priority this round
            random_move(bot_board, dice, &dice_left);
            if (dice_left > 1)
                random_move(opp_board, dice, &dice_left);
            if (dice_left > 1)
                random_move(opp_board, dice, &dice_left);
            if (dice_left > 1)
                random_move(bot_board, dice, &dice_left);
        } else {
            // Opponent has priority this round
            random_move(opp_board, dice, &dice_left);
            if (dice_left > 1)
                random_move(bot_board, dice, &dice_left);
            if (dice_left > 1)
                random_move(bot_board, dice, &dice_left);
            if (dice_left > 1)
                random_move(opp_board, dice, &dice_left);
        }

        free_dice(dice, 5);
        priority = !priority; // Alternate priority for next round
    }
    return 1;
}

int make_move(struct board* b, struct die** dice, struct board* opponent_board,
              struct die** dice_set, int rounds_remaining, int priority) {

    int best_die_index = -1;
    int best_x = -1, best_y = -1;
    double best_score = -1e9;

    // For each die
    for (int i = 0; i < 5; i++) {
        struct die* d = dice[i];
        if (d == NULL)
            continue;

        // For each possible position on the board
        for (int x = 0; x < ROW; x++) {
            for (int y = 0; y < COLUMN; y++) {
                // Check if the die can be placed at this position
                if (!placeable(b, d, x, y))
                    continue;

                double total_score = 0.0;

                for (int sim = 0; sim < get_config()->simulations; sim++) {
                    // Copy boards and dice set for simulation
                    struct board* b_copy = copy_board(b);
                    struct board* opp_copy = copy_board(opponent_board);
                    struct die** dice_set_copy = copy_dice_set(dice_set);

                    struct die** dice_copy = copy_dice(dice, 5);

                    // Apply the move
                    place_die(b_copy, d, x, y); 

                    free_die(dice_copy[i]);
                    dice_copy[i] = NULL;

                    // Simulate the rest of the game
                    if (!simulate_game(b_copy, opp_copy, dice_set_copy, rounds_remaining, priority)) {
                        // This should happen only if there is no more dice left in the dice set
                        free_board(b_copy);
                        free_board(opp_copy);
                        free_dice_copy(dice_copy, 5);
                        free_dice(dice_set_copy, DICE_SET_SIZE);
                        break;
                    }

                    // Calculate the score difference
                    int bot_score = calculate_points(b_copy);
                    int opp_score = calculate_points(opp_copy);
                    int score_diff = bot_score - opp_score;

                    total_score += score_diff;

                    // Free allocated memory
                    free_board(b_copy);
                    free_board(opp_copy);
                    free_dice_copy(dice_copy, 5);
                    free_dice(dice_set_copy, DICE_SET_SIZE);
                }

                double avg_score = total_score / get_config()->simulations;

                if (avg_score > best_score) {
                    best_score = avg_score;
                    best_die_index = i;
                    best_x = x;
                    best_y = y;
                }
            }
        }
    }

    if (best_die_index != -1) {
        place_die(b, dice[best_die_index], best_x, best_y);
        return best_die_index;
    } 
    


    DBG_PRINT("No best move found for us");
    // If this get called it means no move where found, so we are doing
    // the same calculation but inversing the boards
    // This will allow our bot to discard the best die of the opponent
    // and keep the worst die for him

    best_die_index = -1;
    best_x = -1;
    best_y = -1;
    best_score = 1e9;

    // For each die
    for (int i = 0; i < 5; i++) {
        struct die* d = dice[i];
        if (d == NULL)
            continue;

        // For each possible position on the board
        for (int x = 0; x < ROW; x++) {
            for (int y = 0; y < COLUMN; y++) {
                // Check if the die can be placed at this position
                if (!placeable(opponent_board, d, x, y))
                    continue;

                double total_score = 0.0;

                for (int sim = 0; sim < get_config()->simulations; sim++) {
                    // Copy boards and dice set for simulation
                    struct board* b_copy = copy_board(opponent_board);
                    struct board* opp_copy = copy_board(b);
                    struct die** dice_set_copy = copy_dice_set(dice_set);

                    struct die** dice_copy = copy_dice(dice, 5);

                    // Apply the move

                    place_die(b_copy, d, x, y); 

                    free_die(dice_copy[i]);
                    dice_copy[i] = NULL;

                    // Simulate the rest of the game
                    if (!simulate_game(b_copy, opp_copy, dice_set_copy, rounds_remaining, priority)) {
                        // This should happen only if there is no more dice left in the dice set
                        free_board(b_copy);
                        free_board(opp_copy);
                        free_dice_copy(dice_copy, 5);
                        free_dice(dice_set_copy, DICE_SET_SIZE);
                        break;
                    }

                    // Calculate the score difference
                    int bot_score = calculate_points(b_copy);
                    int opp_score = calculate_points(opp_copy);
                    int score_diff = bot_score - opp_score;

                    total_score += score_diff;

                    // Free allocated memory
                    free_board(b_copy);
                    free_board(opp_copy);
                    free_dice_copy(dice_copy, 5);
                    free_dice(dice_set_copy, DICE_SET_SIZE);
                }

                double avg_score = total_score / get_config()->simulations;

                if (avg_score > best_score) {
                    best_score = avg_score;
                    best_die_index = i;
                    best_x = x;
                    best_y = y;
                }
            }
        }
    }



    // We still need to found a place to put the die
    // So we are going to do a random move with the best die of the opponent

    if (best_die_index != -1) {
        int empty_positions[ROW * COLUMN][2];
        int num_positions = 0;

        for (int x = 0; x < ROW; x++) {
            for (int y = 0; y < COLUMN; y++) {
                // only check if the position is empty
                // we already know that the die can't be placed
                // and will be discarded
                if (b->grid[x][y] == NULL) {
                    empty_positions[num_positions][0] = x;
                    empty_positions[num_positions][1] = y;
                    num_positions++;
                }
            }
        }

        int x = empty_positions[rand() % num_positions][0];
        int y = empty_positions[rand() % num_positions][1];


        place_die(b, dice[best_die_index], x, y);
        return best_die_index;
    } 
    




    
    // Lastly if no best move where found for us and for the opponent
    // we are going to discard a random die

    DBG_PRINT("No best move found for ennemy");
    int die_indices[5];
    int num_dice = 0;

    for (int i = 0; i < 5; i++) {
        if (dice[i] != NULL) {
            die_indices[num_dice++] = i;
        }
    }

    int empty_positions[ROW * COLUMN][2];
    int num_positions = 0;

    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COLUMN; y++) {
            // again, only checking if the position is empty
            // we already know that the die can't be placed
            // and will be discarded
            if (b->grid[x][y] == NULL) {
                empty_positions[num_positions][0] = x;
                empty_positions[num_positions][1] = y;
                num_positions++;
            }
        }
    }
    
    int random_index = die_indices[rand() % num_dice];
    DBG_PRINT("Discarding die %d, (e.g. %p)", random_index, (void*)dice[random_index]);

    place_die(b, dice[random_index], empty_positions[rand() % num_positions][0], empty_positions[rand() % num_positions][1]);
    return random_index;
}
