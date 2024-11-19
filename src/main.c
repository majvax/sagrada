#include "board.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void) {
    srand(time(NULL));
    die** dice_set = get_dice_set();
    // TODO: create meaningful names for the boards -_-
    board* b = create_board(); // player's board
    // board* b2 = create_board(); // board of the opponent

    for (int rounds = 1; rounds < 11; rounds++) {
        clear();
        printf("-> TOUR %d\n\n\n", rounds);
        print_board(b);
        printf("\n\n");
        printf("-> Score: %d\n", calculate_points(b));
        printf("-> Voici les des de ce tour\n");

        die** dice = get_dice(dice_set, 5);

        for (int i = 0; i < 5; i++) {
            print_die(dice[i]);
            printf(" ");
            move_up(DIE_ART_LENGTH);
            move_right(DIE_ART_WIDTH + 1);
        }
        move_down(DIE_ART_LENGTH);
        printf("\n");



        int choice = get_int_range("-> Choisissez un de (1-5): ", 1, 5);


        int x = get_int_range("-> Choisissez ou le placer (x): ", 1, COLUMN + 1);
        int y = get_int_range("-> Choisissez ou le placer (y): ", 1, ROW + 1);

        while (place_die(b, dice[choice - 1], y - 1, x - 1) == 0) {
            printf("-> Impossible de placer le de a cet endroit\n");
            x = get_int_range("-> Choisissez ou le placer (x): ", 1, COLUMN + 1);
            y = get_int_range("-> Choisissez ou le placer (y): ", 1, ROW + 1);
        }

        dice[choice - 1] = NULL;

        free_dice(dice, 5);
    }

    free_dice_set(dice_set);

    return 0;
}
