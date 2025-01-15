#include "logic.h"


void player_turn(struct board* player_board, struct die** dice, int dice_left) {
    int choice = get_int_range("-> Choisissez un de (%d-%d): ", 1, dice_left);
    // decrement the choice to match the real index (if dice 1 and 2 are placed, the choice 1 will
    // be the 3rd dice)
    for (int i = 0; i < choice; i++)
        if (dice[i] == NULL)
            choice++;


    int x = get_int_range("-> Choisissez ou le placer (position x de %d a %d): ", 1, COLUMN);
    int y = get_int_range("-> Choisissez ou le placer (position y de %d a %d): ", 1, ROW);

    while (place_die(player_board, dice[choice - 1], y - 1, x - 1) == 0) {
        printf("-> Impossible de placer le de a cet endroit\n");
        x = get_int_range("-> Choisissez ou le placer (position x de %d a %d): ", 1, COLUMN);
        y = get_int_range("-> Choisissez ou le placer (position y de %d a %d): ", 1, ROW);
    }

    free_die(dice[choice - 1]);
    dice[choice - 1] = NULL;
}

void bot_turn(struct board* bot_board, struct board* player_board, struct die** dice, struct die** dice_set_copy, int rounds_remaining, int priority) {
    time_t t = time(NULL);
    int dice_index =
        make_move(bot_board, dice, player_board, dice_set_copy, rounds_remaining, priority);
    free_die(dice[dice_index]);
    dice[dice_index] = NULL;
    while (time(NULL) - t < 1);
}

void round_menu(int rounds, struct board* player_board, struct board* bot_board, struct die** dice) {
    clear();
    printf("-> TOUR %d\n\n\n", rounds);
    print_boards(player_board, bot_board);
    printf("\n\n");
    printf("-> Votre score: %d\n-> Score adverse: %d\n\n", calculate_points(player_board),
           calculate_points(bot_board));
    printf("-> Voici les des de ce tour\n");
    print_dice(dice, 5);
    printf("\n");
}

void play_round(int rounds, struct die** dice_set, struct board* player_board, struct board* bot_board, int priority) {
    struct die** dice = get_dice(dice_set, 5);
    int dice_left = 5;
    int rounds_remaining = 11 - rounds;

    round_menu(rounds, player_board, bot_board, dice);



    // bot against bot for testing purposes
    // if (priority) {
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    // } else {
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    // }

    // free_dice(dice, 5);
    // return;



    if (priority) {
        player_turn(player_board, dice, dice_left--);
        round_menu(rounds, player_board, bot_board, dice);
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
        round_menu(rounds, player_board, bot_board, dice);
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
        round_menu(rounds, player_board, bot_board, dice);
        player_turn(player_board, dice, dice_left--);
    } else {
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
        round_menu(rounds, player_board, bot_board, dice);
        player_turn(player_board, dice, dice_left--);
        round_menu(rounds, player_board, bot_board, dice);
        player_turn(player_board, dice, dice_left--);
        round_menu(rounds, player_board, bot_board, dice);
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
    }

    free_dice(dice, 5);
}

void play_game(struct board* player_board, struct board* bot_board, struct die** dice_set) {
    int priority = rand() % 2;

    for (int rounds = 1; rounds < 11; rounds++) {
        play_round(rounds, dice_set, player_board, bot_board, priority);
        priority = !priority;
    }

    clear();
    print_boards(player_board, bot_board);
    printf("\n\n");
    printf("-> Votre score: %d\n-> Score adverse: %d\n\n", calculate_points(player_board),
           calculate_points(bot_board));

    if (calculate_points(player_board) > calculate_points(bot_board)) {
        printf("-> Vous avez gagne!\n");
    } else if (calculate_points(player_board) < calculate_points(bot_board)) {
        printf("-> Vous avez perdu!\n");
    } else {
        printf("-> Egalite!\n");
    }}

void game_menu() {
    for (;;) {
        clear();
        printf("-> BIENVENUE DANS LE JEU DE SAGRADA\n\n");
        printf("  -> 1. Jouer\n");
        printf("  -> 2. Regles\n");
        printf("  -> 3. Configurations\n");
        printf("  -> 4. Quitter\n\n");

        int choice = get_int_range("-> Choisissez une option (%d-%d): ", 1, 4);

        switch (choice) {
            case 1: return;
            case 2: clear(); print_rules(); wait_for_enter(); break;
            case 3: clear(); print_config(); wait_for_enter(); break;
            case 4: exit(0);
        }
    }
}

void print_rules() {
    printf("-> REGLES\n\n");
    printf("  -> Le jeu se joue en 10 tours\n");
    printf("  -> A chaque tour, 5 des sont tires aleatoirement d'un sac de 90 des\n");
    printf("  -> Un des 2 joueurs est choisis aleatoirement pour etre le premier joueur, a chaque tour les roles sont inverse\n");
    printf("  -> Le premier joueur choisit un de et le place sur son plateau\n");
    printf("  -> Le deuxieme joueur choisit deux des et les place sur son plateau\n");
    printf("  -> Le premier joueur choisit un dernier de et les place sur son plateau\n");
    printf("  -> Finalement, le dernier de est defausse\n\n");

    printf("  -> Les des doivent etre places sur le plateau d'une maniere speciale pour gagner des points:\n");
    printf("    -> Chaque ligne contenant 5 des de valeurs differentes rapporte 5 points\n");
    printf("    -> Chaque colonne contenant 4 des de couleurs differentes rapporte 5 points\n");
    printf("    -> Chaque de de couleur violet rapport un nombre de points equivalents a sa valeur\n\n");

    printf("  -> Le joueur avec le plus de points a la fin des 10 tours gagne\n\n");

    printf("-> Appuyez sur 'entrer' pour revenir au menu\n");
} 
