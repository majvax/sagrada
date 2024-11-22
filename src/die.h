#ifndef DIE_H
#define DIE_H

#include "color.h"
#include "terminal.h"
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
extern void free_die(die* d);

extern die** get_dice_set();
extern void free_dice_set(die** dice_set);
extern die** copy_dice_set(die** dice_set);
extern die* get_random_die(die** dice_set);

extern die** get_dice(die** dice_set, int number);
extern void free_dice(die** dice_set, int size);

char** get_ascii_die(die* d);
void print_die(die* d);
void print_dice(die** dice, int size);

#endif // DIE_H
