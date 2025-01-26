#ifndef BOARD_H
#define BOARD_H

#include "color.h"
#include "die.h"
#include "exit.h"


#define ROW 4
#define COLUMN 5


struct board {
    struct die* grid[ROW][COLUMN];
    int first_die_placed;
}; // 4*5*sizeof(die) + sizeof(int) = 160 bytes

extern struct board* create_board();
extern struct board* copy_board(struct board* b);
extern void free_board(struct board* b);
extern int place_die(struct board* b, struct die* d, int posx, int posy);

extern int calculate_points(struct board* b);
extern int placeable(struct board* b, int posx, int posy);


#endif // BOARD_H
