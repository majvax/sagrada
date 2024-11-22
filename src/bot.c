#include "bot.h"






int calculate_die_pos_points_potential(board* b, die* d, int x, int y) {
    board* b_copy = copy_board(b);
    place_die(b_copy, d, x, y);
    return calculate_points(b_copy);    
}

int make_move(board* b, die** dice) {
    int points = -1;
    int x, y;
    int best_die = -1;


    // for each die, calculate the potential points of each position
    for (int i = 0; i < 5; i++) {
        die* d = dice[i];
        if (d == NULL)
            continue;
        for (int j = 0; j < ROW; j++) {
            for (int k = 0; k < COLUMN; k++) {
                if (b->grid[j][k] == NULL) {
                    int potential_points = calculate_die_pos_points_potential(b, d, j, k);
                    if (potential_points > points) {
                        points = potential_points;
                        x = j;
                        y = k;
                        best_die = i;
                    }
                }
            }
        }
    }

    place_die(b, dice[best_die], x, y);
    return best_die;
}
