#include "logic.h"
#include "name.h"


void player_turn(struct Game* game, struct board* board, int dice_left) {
    int choice, x, y, response;
    do {
        choice = get_int_range("-> Choisissez un de (%d-%d): ", 1, dice_left);
        // decrement the choice to match the real index (if dice 1 and 2 are placed, the choice 1 will
        // be the 3rd dice)
        for (int i = 0; i < choice; i++)
            if (game->dice[i] == NULL)
                choice++;


        x = get_int_range("-> Choisissez ou le placer (position x de %d a %d): ", 1, COLUMN);
        y = get_int_range("-> Choisissez ou le placer (position y de %d a %d): ", 1, ROW);

        response = place_die(board, game->dice[choice - 1], y - 1, x - 1);
        if (response == DIE_LOST)
            printf("-> Impossible de placer le de a cet endroit\n");
    } while (response == DIE_NOT_PLACED);

    free_die(game->dice[choice - 1]);
    game->dice[choice - 1] = NULL;
}

void bot_turn(struct Game* game, struct board* board1, struct board* board2, int rounds_remaining) {
    time_t t = time(NULL);
    int dice_index =
        make_move(board1, game->dice, board2, game->dice_set, rounds_remaining, game->priority);
    free_die(game->dice[dice_index]);
    game->dice[dice_index] = NULL;
    while (time(NULL) - t < 1)
        ;
}

void play_game(struct Game* game) {
    game->priority = rand() % 2;

    
    if (game->mode == 2) {
        game->player1 = ask_for_name("-> Entrez le nom du joueur 1: ");
        game->player2 = ask_for_name("-> Entrez le nom du joueur 2: ");
    } else if (game->mode == 1) {
        game->player1 = ask_for_name("-> Entrez le nom du joueur 1: ");
        game->player2 = get_random_name();
    } else {
        game->player1 = get_random_name();
        game->player2 = get_random_name();
    }


    for (int rounds = 1; rounds < 11; rounds++) {
        if (game->mode == 1)
            player_against_bot(game, rounds);
        else if (game->mode == 2)
            player_against_player(game, rounds);
        else
            bot_against_bot(game, rounds);

        game->priority = !game->priority;
    }

    clear();
    print_boards(game->player_board, game->bot_board);
    printf("\n\n");
    printf("-> Score de %s: %d\n-> Score de %s: %d\n\n",
        game->player1,
        calculate_points(game->player_board),
        game->player2,
        calculate_points(game->bot_board));

    if (calculate_points(game->player_board) > calculate_points(game->bot_board)) {
        printf("-> %s a gagne\n", game->player1);
    } else if (calculate_points(game->player_board) < calculate_points(game->bot_board)) {
        printf("-> %s a gagne\n", game->player2);
    } else {
        printf("-> C'est une Egalite!\n");
    }
}

int game_menu() {
    for (;;) {
        clear();
        printf("-> BIENVENUE DANS LE JEU DE SAGRADA\n\n");
        printf("  -> 1. Partie a 1 joueur\n");
        printf("  -> 2. Partie a 2 joueurs\n");
        printf("  -> 3. Partie a 2 bots\n");
        printf("  -> 4. Regles\n");
        printf("  -> 5. Configurations\n");
        printf("  -> 6. Quitter\n\n");

        int choice = get_int_range("-> Choisissez une option (%d-%d): ", 1, 6);

        switch (choice) {
        case 1:
        case 2:
        case 3:
            return choice;
        case 4:
            clear();
            print_rules();
            wait_for_enter();
            break;
        case 5:
            clear();
            print_config();
            wait_for_enter();
            break;
        case 6:
            exit(0);
        }
    }
}

void print_rules() {
    printf("-> REGLES\n\n");
    printf("  -> Le jeu se joue en 10 tours\n");
    printf("  -> A chaque tour, 5 des sont tires aleatoirement d'un sac de 90 des\n");
    printf("  -> Un des 2 joueurs est choisis aleatoirement pour etre le premier joueur, a chaque "
           "tour les roles sont inverse\n");
    printf("  -> Le premier joueur choisit un de et le place sur son plateau\n");
    printf("  -> Le deuxieme joueur choisit deux des et les place sur son plateau\n");
    printf("  -> Le premier joueur choisit un dernier de et les place sur son plateau\n");
    printf("  -> Finalement, le dernier de est defausse\n\n");

    printf("  -> Les des doivent etre places sur le plateau d'une maniere speciale pour gagner des "
           "points:\n");
    printf("    -> Chaque ligne contenant 5 des de valeurs differentes rapporte 5 points\n");
    printf("    -> Chaque colonne contenant 4 des de couleurs differentes rapporte 5 points\n");
    printf("    -> Chaque de de couleur violet rapport un nombre de points equivalents a sa "
           "valeur\n\n");

    printf("  -> Le joueur avec le plus de points a la fin des 10 tours gagne\n\n");

    printf("-> Appuyez sur 'entrer' pour revenir au menu\n");
}

void round_menu(struct Game* game, int rounds, char* player_name) {
    clear();
    printf("-> TOUR %d\n", rounds);
    printf("-> C'est au tour de %s de placer un de\n\n", player_name);

    print_boards(game->player_board, game->bot_board);
    printf("\n\n");
    printf("-> Score de %s: %d\n-> Score de %s: %d\n\n",
        game->player1,
        calculate_points(game->player_board),
        game->player2,
        calculate_points(game->bot_board));

    printf("-> Voici les des de ce tour\n\n");
    print_dice(game->dice, 5);
    printf("\n");

}

void player_against_bot(struct Game* game, int rounds) {
    game->dice = get_dice(game->dice_set, 5);
    if (game->dice == NULL) {
        printf("-> Plus de des disponibles\n");
        return;
    }
    int dice_left = 5;
    int rounds_remaining = 11 - rounds;

    // round_menu(game, rounds, NULL);

    if (game->priority) {
        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);

        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);
        dice_left--;

        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);
        dice_left--;

        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);
    } else {
        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);
        dice_left--;

        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);

        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);

        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);
        dice_left--;
    }

    free_dice(game->dice, 5);
}

void bot_against_bot(struct Game* game, int rounds) {
    game->dice = get_dice(game->dice_set, 5);
    if (game->dice == NULL) {
        printf("-> Plus de des disponibles\n");
        return;
    }
    int rounds_remaining = 11 - rounds;

    // round_menu(game, rounds);



    if (game->priority) {
        round_menu(game, rounds, game->player1);
        bot_turn(game, game->player_board, game->bot_board, rounds_remaining);

        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);

        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);

        round_menu(game, rounds, game->player1);
        bot_turn(game, game->player_board, game->bot_board, rounds_remaining);

    } else {
        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);

        round_menu(game, rounds, game->player1);
        bot_turn(game, game->player_board, game->bot_board, rounds_remaining);

        round_menu(game, rounds, game->player1);
        bot_turn(game, game->player_board, game->bot_board, rounds_remaining);

        round_menu(game, rounds, game->player2);
        bot_turn(game, game->bot_board, game->player_board, rounds_remaining);

    }

    free_dice(game->dice, 5);
}

void player_against_player(struct Game* game, int rounds) {
    game->dice = get_dice(game->dice_set, 5);
    if (game->dice == NULL) {
        printf("-> Plus de des disponibles\n");
        return;
    }
    int dice_left = 5;

    // round_menu(game, rounds);



    if (game->priority) {
        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);

        round_menu(game, rounds, game->player2);
        player_turn(game, game->bot_board, dice_left--);

        round_menu(game, rounds, game->player2);
        player_turn(game, game->bot_board, dice_left--);

        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);

    } else {
        round_menu(game, rounds, game->player2);
        player_turn(game, game->bot_board, dice_left--);

        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);

        round_menu(game, rounds, game->player1);
        player_turn(game, game->player_board, dice_left--);

        round_menu(game, rounds, game->player2);
        player_turn(game, game->bot_board, dice_left--);

    }

    free_dice(game->dice, 5);
}

