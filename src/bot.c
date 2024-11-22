#include "bot.h"


void bot_random_move(board* b, die** dice, int* dice_left) {
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
    die* d = dice[die_index];

    int empty_positions[ROW * COLUMN][2];
    int num_positions = 0;

    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COLUMN; y++) {
            if (b->grid[x][y] == NULL) {
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

void opponent_random_move(board* b, die** dice, int* dice_left) {
    bot_random_move(b, dice, dice_left);
}

void simulate_game(board* bot_board, board* opp_board, die** dice, int depth) {
    int dice_left = 5;
    // Count the number of dice left
    for (int i = 0; i < 5; i++) {
        if (dice[i] == NULL) {
            dice_left--;
        }
    }

    // FIXME: Implement the game simulation not only the current round
    for (int d = 0; d < depth; d++) {
        if (dice_left <= 0)
            break;

        // Bot's turn
        bot_random_move(bot_board, dice, &dice_left);

        if (dice_left <= 0)
            break;

        // Opponent's turn
        opponent_random_move(opp_board, dice, &dice_left);
    }
}

int make_move(board* b, die** dice, board* opponent_board) {
    int best_die_index = -1;
    int best_x = -1, best_y = -1;
    double best_score = -1e9;

    // For each die
    for (int i = 0; i < 5; i++) {
        die* d = dice[i];
        if (d == NULL)
            continue;

        // For each possible position on the board
        for (int x = 0; x < ROW; x++) {
            for (int y = 0; y < COLUMN; y++) {
                if (b->grid[x][y] != NULL)
                    continue;

                double total_score = 0.0;

                for (int sim = 0; sim < SIMULATIONS; sim++) {
                    board* b_copy = copy_board(b);
                    board* opp_copy = copy_board(opponent_board);

                    die** dice_copy = copy_dice(dice, 5);

                    // Apply the move
                    place_die(b_copy, d, x, y);
                    free_die(dice_copy[i]);
                    dice_copy[i] = NULL;

                    simulate_game(b_copy, opp_copy, dice_copy, SIMULATION_DEPTH);

                    // Calculate the score difference
                    int bot_score = calculate_points(b_copy);
                    int opp_score = calculate_points(opp_copy);
                    int score_diff = bot_score - opp_score;

                    total_score += score_diff;

                    free_board(b_copy);
                    free_board(opp_copy);
                    free_dice_copy(dice_copy, 5);
                }

                double avg_score = total_score / SIMULATIONS;

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
    } else {
        return -1;
    }
}
