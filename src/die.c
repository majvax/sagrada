#include "die.h"


char* die_1[5] = {
    "+-------+", "|       |", "|   O   |", "|       |", "+-------+",
};

char* die_2[5] = {
    "+-------+", "| O     |", "|       |", "|     O |", "+-------+",
};

char* die_3[5] = {
    "+-------+", "| O     |", "|   O   |", "|     O |", "+-------+",
};

char* die_4[5] = {
    "+-------+", "| O   O |", "|       |", "| O   O |", "+-------+",
};

char* die_5[5] = {
    "+-------+", "| O   O |", "|   O   |", "| O   O |", "+-------+",
};

char* die_6[5] = {
    "+-------+", "| O   O |", "| O   O |", "| O   O |", "+-------+",
};

char* die_empty[5] = {"+-------+", "|       |", "|       |", "|       |", "+-------+"};

die* create_die(int color, int value) {
    // allocating 8 bytes
    die* d = malloc(sizeof(die));
    assert(d != NULL && "get_die_from_col_and_val: Memory allocation failed");
    d->value = value;
    d->color = color;
    return d;
}

void free_die(die* d) { free(d); }

die** get_dice_set() {
    // Allocate memory for an array of 90 die pointers
    // 90 * sizeof(die*) = 90 * 8 = 720 bytes allocated
    die** dice_set = malloc(sizeof(die*) * DICE_SET_SIZE);
    assert(dice_set != NULL && "get_dice_set: Memory allocation failed");

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

void free_dice_set(die** dice_set) {
    for (int i = 0; i < DICE_SET_SIZE; i++) {
        if (dice_set[i] != NULL)
            free_die(dice_set[i]);
    }
    free(dice_set);
}

die** copy_dice_set(die** dice_set) {
    die** copy = malloc(sizeof(die*) * DICE_SET_SIZE);
    assert(copy != NULL && "copy_dice_set: Memory allocation failed");
    for (int i = 0; i < DICE_SET_SIZE; i++) {
        die* d = dice_set[i];
        copy[i] = create_die(d->color, d->value);
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
    for (int i = 0; i < size; i++) {
        free_die(dice_set[i]);
    }
    free(dice_set);
}

char** get_ascii_die(die* d) {
    if (d == NULL) {
        return die_empty;
    }
    switch (d->value) {
    case 1:
        return die_1;
    case 2:
        return die_2;
    case 3:
        return die_3;
    case 4:
        return die_4;
    case 5:
        return die_5;
    default:
        return die_6;
    }
}


void print_die(die* d) {
    char* color = (d != NULL) ? get_ansi_code(d->color) : ANSI_RESET;
    char** art = get_ascii_die(d);

    for (int k = 0; k < DIE_ART_LENGTH; k++) {
        printf("%s%s%s ", color, art[k], ANSI_RESET);
        move_left(DIE_ART_WIDTH + 1);
        move_down(1);
    }
}
