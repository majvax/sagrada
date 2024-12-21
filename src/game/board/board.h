#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "color.h"
#include "die.h"


#define ROW 4
#define COLUMN 5


#define EXTRA_RULES 0 // 1 if extra rule is enabled, 0 otherwise


typedef struct {
    die* grid[ROW][COLUMN];
} board; // 4*5*sizeof(die) + sizeof(int) = 160 bytes

extern board* create_board();
extern board* copy_board(board* b);
extern void free_board(board* b);
extern bool place_die(board* b, die* d, int posx, int posy);

extern int calculate_points(board* b);



#endif // BOARD_H
