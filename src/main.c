#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "logic.h"



int main(void) {
    srand((unsigned)time(NULL));

    if (!init_config(DEFAULT_CONFIG_FILE)) {
        printf("-> Fichier de configuration introuvable\n\t-> Creation du fichier de configuration "
               "par defaut...\n");
        printf("-> Appuyez sur 'entrer' pour acceder au menu\n");
        scanf("%*c");
    }
    
    // Récupère le mode de jeu choisi par l'utilisateur
    int mode = game_menu();


    // Alloue la mémoire utilisé pour le jeu
    struct Game game;
    game.player_board = create_board();
    game.bot_board    = create_board();
    game.dice_set     = create_dice_set();
    game.mode         = mode;


    play_game(&game);


    // Libère la mémoire
    free_board(game.player_board);
    free_board(game.bot_board);
    free_dice(game.dice_set, DICE_SET_SIZE);
    free_config();


    return 0;
}
