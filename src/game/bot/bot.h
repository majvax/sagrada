#include "board.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>



extern int make_move(struct board* b, struct die** dice, struct board* opponent_board,
                     struct die** dice_set, int rounds_remaining, int priority);
