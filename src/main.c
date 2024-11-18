#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

const char *colors[5] = {"blue", "yellow", "red", "green", "purple"};


int main(void) {
    srand(time(NULL));
    die **dice_set = get_dice_set();
    board *b = create_board();

    for (int rounds = 1; rounds < 11; rounds++) {
        printf("---------TOUR %d---------\n", rounds);
        print_board(b);

        die **dice = get_dice(dice_set, 5);

        for (int i = 0; i < 5; i++) {
            printf("Vous avez tire un de: %s%d %s\n\e[0;37m",
                   get_ascii_code(dice[i]->color), dice[i]->value,
                   colors[dice[i]->color]);
        }
        printf("\n");

        int row=-1, column=-1;
        int c=0, v=0;
        char c_;
        printf("Choisissez votre de (c, v): ");
        scanf(" %c, %d", &c_, &v);
        c = get_color_code(c_);

        for (int i = 0; i < 5; i++) {
            if (c == dice[i]->color && v == dice[i]->value) {
                printf("Ou le placer (x, y): ");
                scanf("%d, %d", &row, &column);

                if (!place_die(b, dice[i], row, column)) {
                    printf("Un de est deja a cet emplacement !, %d, %s\n",
                           b->grid[row][column]->value,
                           colors[b->grid[row][column]->color]);
                    return 0;
                }
            }
        }

        printf("Score: %d\n", calculate_points(b));

        free_dice(dice, 5);
        printf("\n\n");
    }

    free_dice_set(dice_set);

    return 0;
}
