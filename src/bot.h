#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define SIMULATIONS 100000
#define SIMULATION_DEPTH 20


extern int make_move(board* b, die** dice, board* opponent_board);
