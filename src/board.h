#ifndef BOARD_H
#define BOARD_H

#include "color.h"
#include "die.h"

#define ROW 4
#define COLUMN 5

#define BOARD_ART_LENGTH DIE_ART_LENGTH* ROW
#define BOARD_ART_WIDTH DIE_ART_WIDTH* COLUMN
#define EXTRA_RULES 1 // 1 if extra rule is enabled, 0 otherwise


typedef struct {
    die* grid[ROW][COLUMN];
} board; // 4*5*sizeof(die) + sizeof(int) = 160 bytes

extern board* create_board();
extern board* copy_board(board* b);
extern void free_board(board* b);
extern int place_die(board* b, die* d, int posx, int posy);

extern int calculate_points(board* b);

extern void print_boards(board* b, board* b2);


#endif // BOARD_H
