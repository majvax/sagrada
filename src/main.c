#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "config.h"
#include "argparser.h"


int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));

    if (!init_config(DEFAULT_CONFIG_FILE)) {
        printf("-> Fichier de configuration introuvable\n\t-> Creation du fichier de configuration par defaut...\n");
        scanf("%*c");
    }

    if (!parse_args(argc, argv)) {
        return 0;
    }

    game_menu();


    die** dice_set = create_dice_set();
    board* player_board = create_board();
    board* bot_board = create_board();


    play_game(player_board, bot_board, dice_set);


    free_board(player_board);
    free_board(bot_board);
    free_dice(dice_set, DICE_SET_SIZE);
    free_config();


    return 0;
}
