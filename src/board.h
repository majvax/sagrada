#include "color.h"
#include "die.h"

#define ROW 4
#define COLUMN 5

#define BOARD_ART_LENGTH DIE_ART_LENGTH* ROW
#define BOARD_ART_WIDTH DIE_ART_WIDTH* COLUMN



typedef struct {
    die* grid[ROW][COLUMN];
    int score;
    int prediction;
} board; // 4*5*sizeof(die) + 2*sizeof(int) = 168 bytes

extern board* create_board();
extern void free_board(board* b);
extern int place_die(board* b, die* d, int posx, int posy);

extern int calculate_points(board* b);

extern void print_board(board* b);
