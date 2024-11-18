#include "die.h"

die *create_die(int color, int value) {
    die *d = malloc(sizeof(die));
    assert(d != NULL && "get_die_from_col_and_val: Memory allocation failed");
    d->value = value;
    d->color = color;
    d->is_used = 0;
    return d;
}

void free_die(die *d) { free(d); }

die **get_dice_set() {
    // Allocate memory for an array of 90 die pointers
    die **dice_set = malloc(sizeof(die *) * 90);
    assert(dice_set != NULL && "get_dice_set: Memory allocation failed");

    int index = 0;
    // create 3 dice for each value of each color
    for (int color = 0; color < 5; color++) {
        for (int value = 1; value <= 6; value++) {
            for (int count = 0; count < 3; count++) {
                die *d = create_die(color, value);
                if (d == NULL) {
                    // Handle memory allocation failure for a die
                    for (int k = 0; k < index; k++) {
                        free_die(dice_set[k]);
                    }
                    // not calling destroy_dice_set because dice_set is not
                    // fully initialized
                    free(dice_set);
                    return NULL;
                }
                dice_set[index++] = d;
            }
        }
    }
    return dice_set;
}

void free_dice_set(die **dice_set) {
    for (int i = 0; i < 90; i++) {
        free_die(dice_set[i]);
    }
    free(dice_set);
}

die **copy_dice_set(die **dice_set) {
    die **copy = malloc(sizeof(die *) * 90);
    assert(copy != NULL && "copy_dice_set: Memory allocation failed");
    for (int i = 0; i < 90; i++) {
        die *d = dice_set[i];
        copy[i] = create_die(d->color, d->value);
    }
    return copy;
}

die *get_random_die(die **dice_set) {
    int index = rand() % 90;
    die *d = dice_set[index];
    while (d->is_used) {
        index = rand() % 90;
        d = dice_set[index];
    }
    d->is_used = 1;
    return d;
}

die **get_dice(die **dice_set, int number) {
    die **dice = malloc(sizeof(die *) * number);
    assert(dice != NULL && "get_dice: Memory allocation failed");
    for (int i = 0; i < number; i++) {
        dice[i] = get_random_die(dice_set);
    }
    return dice;
}

void free_dice(die **dice_set, int size) {
    for (int i = 0; i < size; i++) {
        free_die(dice_set[i]);
    }
    free(dice_set);
}
