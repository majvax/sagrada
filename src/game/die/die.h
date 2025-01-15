#ifndef DIE_H
#define DIE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DICE_SET_SIZE 90
#define DIE_ART_LENGTH 5
#define DIE_ART_WIDTH 9

struct die {
    int value;
    int color;
}; // 8 bytes

extern struct die* create_die(int color, int value);
extern struct die* copy_die(struct die* d);
extern void free_die(struct die* d);

extern struct die** create_dice_set();
extern struct die** copy_dice_set(struct die** dice_set);

extern struct die** copy_dice(struct die** dice, int size);
extern void free_dice_copy(struct die** dice_copy, int size);

// extern struct die** copy_dice_array(struct die** dice, int size);
extern struct die* get_random_die(struct die** dice_set);

extern struct die** get_dice(struct die** dice_set, int number);
extern void free_dice(struct die** dice_set, int size);



#endif // DIE_H
