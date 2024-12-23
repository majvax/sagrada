#include "die.h"



die* create_die(int color, int value) {
    // allocating 8 bytes
    die* d = malloc(sizeof(die));
    assert(d != NULL && "get_die_from_col_and_val: Memory allocation failed");
    d->value = value;
    d->color = color;
    return d;
}

die* copy_die(die* d) {
    if (d == NULL)
        return NULL;
    return create_die(d->color, d->value);
}

void free_die(die* d) {
    if (d != NULL)
        free(d);
}

die** create_dice_set() {
    // Allocate memory for an array of 90 die pointers
    // 90 * sizeof(die*) = 90 * 8 = 720 bytes allocated
    die** dice_set = malloc(sizeof(die*) * DICE_SET_SIZE);
    assert(dice_set != NULL && "create_dice_set: Memory allocation failed");

    int index = 0;
    // create 3 dice for each value of each color
    for (int color = 0; color < 5; color++) {
        for (int value = 1; value <= 6; value++) {
            for (int count = 0; count < 3; count++) {
                die* d = create_die(color, value);
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

die** copy_dice_set(die** dice_set) {
    die** copy = malloc(sizeof(die*) * DICE_SET_SIZE);
    assert(copy != NULL && "copy_dice_set: Memory allocation failed");
    for (int i = 0; i < DICE_SET_SIZE; i++) {
        die* d = dice_set[i];
        if (d != NULL)
            copy[i] = create_die(d->color, d->value);
        else
            copy[i] = NULL;
    }
    return copy;
}

die** copy_dice(die** dice, int size) {
    die** dice_copy = (die**)malloc(sizeof(die*) * size);
    assert(dice_copy != NULL && "copy_dice: Memory allocation failed");
    for (int i = 0; i < size; i++) {
        dice_copy[i] = copy_die(dice[i]);
    }
    return dice_copy;
}

void free_dice_copy(die** dice_copy, int size) {
    for (int i = 0; i < size; i++) {
        if (dice_copy[i] != NULL) {
            free_die(dice_copy[i]);
            dice_copy[i] = NULL;
        }
    }
    free(dice_copy);
}

die** copy_dice_array(die** dice_set, int size) {
    die** copy = malloc(sizeof(die*) * size);
    assert(copy != NULL && "copy_dice_set: Memory allocation failed");
    for (int i = 0; i < size; i++) {
        die* d = dice_set[i];
        if (d != NULL)
            copy[i] = create_die(d->color, d->value);
        else
            copy[i] = NULL;
    }
    return copy;
}

die* get_random_die(die** dice_set) {
    int start_index = rand() % DICE_SET_SIZE;
    int index = start_index;

    do {
        if (dice_set[index] != NULL) {
            die* d = dice_set[index];
            dice_set[index] = NULL;
            return d;
        }
        index = (index + 1) % DICE_SET_SIZE;
    } while (index != start_index);

    return NULL;
}

die** get_dice(die** dice_set, int number) {
    die** dice = malloc(sizeof(die*) * number);
    assert(dice != NULL && "get_dice: Memory allocation failed");
    for (int i = 0; i < number; i++) {
        dice[i] = get_random_die(dice_set);
    }
    return dice;
}

void free_dice(die** dice_set, int size) {
    if (dice_set == NULL)
        return;
    for (int i = 0; i < size; i++) {
        if (dice_set[i] != NULL) {
            free_die(dice_set[i]);
            dice_set[i] = NULL;
        }
    }
    free(dice_set);
}
