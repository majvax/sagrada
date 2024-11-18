#include "die.h"
#include "color.h"

#define ROW 4
#define COLUMN 5


typedef struct {
    die* grid[ROW][COLUMN];
    int score;
    int prediction;
} board;


extern board* create_board();
extern void free_board(board* b);
extern int place_die(board* b, die* d, int posx, int posy);

extern int calculate_points(board* b);

extern void print_board(board* b);
