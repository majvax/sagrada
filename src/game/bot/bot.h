#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "board.h"


extern int make_move(board* b, die** dice, board* opponent_board, die** dice_set,
                     int rounds_remaining, int priority);
