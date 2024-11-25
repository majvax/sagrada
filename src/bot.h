#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define SIMULATIONS 1000

extern int make_move(board* b, die** dice, board* opponent_board, die** dice_set, int rounds_remaining, int priority);
