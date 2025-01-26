#include "die.h"
#include "exit.h"

struct die* create_die(int color, int value) {
    // allocating 8 bytes
    struct die* d = malloc(sizeof(struct die));
    PRINT_AND_DIE_IF_COND_NOT_MEET(d == NULL, "Memory allocation failed", 1);

    d->value = value;
    d->color = color;
    return d;
}

struct die* copy_die(struct die* d) {
    if (d == NULL)
        return NULL;
    return create_die(d->color, d->value);
}

void free_die(struct die* d) {
    if (d != NULL)
        free(d);
}

struct die** create_dice_set() {
    // Allocate memory for an array of 90 die pointers
    // 90 * sizeof(struct die*) = 90 * 8 = 720 bytes allocated
    struct die** dice_set = malloc(sizeof(struct die*) * DICE_SET_SIZE);

    int index = 0;
    // create 3 dice for each value of each color
    for (int color = 0; color < 5; color++) {
        for (int value = 1; value <= 6; value++) {
            for (int count = 0; count < 3; count++) {
                struct die* d = create_die(color, value);
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

struct die** copy_dice_set(struct die** dice_set) {
    struct die** copy = malloc(sizeof(struct die*) * DICE_SET_SIZE);
    PRINT_AND_DIE_IF_COND_NOT_MEET(copy == NULL, "Memory allocation failed", 1);


    for (int i = 0; i < DICE_SET_SIZE; i++) {
        struct die* d = dice_set[i];
        if (d != NULL)
            copy[i] = create_die(d->color, d->value);
        else
            copy[i] = NULL;
    }
    return copy;
}

struct die** copy_dice(struct die** dice, int size) {
    struct die** dice_copy = (struct die**)malloc(sizeof(struct die*) * size);
    PRINT_AND_DIE_IF_COND_NOT_MEET(dice_copy == NULL, "Memory allocation failed", 1);

    for (int i = 0; i < size; i++) {
        dice_copy[i] = copy_die(dice[i]);
    }
    return dice_copy;
}

void free_dice_copy(struct die** dice_copy, int size) {
    for (int i = 0; i < size; i++) {
        if (dice_copy[i] != NULL) {
            free_die(dice_copy[i]);
            dice_copy[i] = NULL;
        }
    }
    free(dice_copy);
}

struct die** copy_dice_array(struct die** dice_set, int size) {
    struct die** copy = malloc(sizeof(struct die*) * size);
    PRINT_AND_DIE_IF_COND_NOT_MEET(copy == NULL, "Memory allocation failed", 1);

    for (int i = 0; i < size; i++) {
        struct die* d = dice_set[i];
        if (d != NULL)
            copy[i] = create_die(d->color, d->value);
        else
            copy[i] = NULL;
    }
    return copy;
}

struct die* get_random_die(struct die** dice_set) {
    int start_index = rand() % DICE_SET_SIZE;
    int index = start_index;

    do {
        if (dice_set[index] != NULL) {
            struct die* d = dice_set[index];
            dice_set[index] = NULL;
            return d;
        }
        index = (index + 1) % DICE_SET_SIZE;
    } while (index != start_index);

    return NULL;
}

struct die** get_dice(struct die** dice_set, int number) {
    struct die** dice = malloc(sizeof(struct die*) * number);
    PRINT_AND_DIE_IF_COND_NOT_MEET(dice == NULL, "Memory allocation failed", 1);
    int num_of_null = 0;
    for (int i = 0; i < number; i++) {
        dice[i] = get_random_die(dice_set);
        if (dice[i] == NULL)
            num_of_null++;
    }
    if (num_of_null == number) {
        free(dice);
        return NULL;
    }
    return dice;
}

void free_dice(struct die** dice_set, int size) {
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
