#ifndef DIE_H
#define DIE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DICE_SET_SIZE 90
#define DIE_ART_LENGTH 5
#define DIE_ART_WIDTH 9

typedef struct {
    int value;
    int color;
} die; // 8 bytes

extern die* create_die(int color, int value);
extern die* copy_die(die* d);
extern void free_die(die* d);

extern die** create_dice_set();
extern die** copy_dice_set(die** dice_set);

extern die** copy_dice(die** dice, int size);
extern void free_dice_copy(die** dice_copy, int size);

extern die** copy_dice_array(die** dice, int size);
extern die* get_random_die(die** dice_set);

extern die** get_dice(die** dice_set, int number);
extern void free_dice(die** dice_set, int size);



#endif // DIE_H
