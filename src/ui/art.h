#ifndef ART_H
#define ART_H

#include "die.h"
#include "board.h"
#include "terminal.h"
#include "color.h"



#define BOARD_ART_LENGTH DIE_ART_LENGTH* ROW
#define BOARD_ART_WIDTH DIE_ART_WIDTH* COLUMN



extern const char** get_ascii_die(struct die* d);
extern void print_die(struct die* d);
extern void print_dice(struct die** dice, int size);
extern void print_boards(struct board* b, struct board* b2);


extern const char* die_1[5];
extern const char* die_2[5];
extern const char* die_3[5];
extern const char* die_4[5];
extern const char* die_5[5];
extern const char* die_6[5];
extern const char* die_empty[5];




#endif // ART_H
