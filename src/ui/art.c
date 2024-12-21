#include "art.h"

const char** get_ascii_die(die* d) {
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
    const char** art = get_ascii_die(d);

    for (int k = 0; k < DIE_ART_LENGTH; k++) {
        printf("%s%s%s ", color, art[k], ANSI_RESET);
        move_left(DIE_ART_WIDTH + 1);
        move_down(1);
    }
}

void print_dice(die** dice, int size) {
    for (int i = 0; i < size; i++) {
        if (dice[i] == NULL)
            continue;
        print_die(dice[i]);
        printf(" ");
        move_up(DIE_ART_LENGTH);
        move_right(DIE_ART_WIDTH + 1);
    }
    move_down(DIE_ART_LENGTH);
}

void print_boards(board* b, board* b2) {
    for (int i = 0; i < ROW; i++) {
        printf("\t");
        for (int j = 0; j < COLUMN; j++) {
            die* d = b->grid[i][j];

            print_die(d);

            move_up(DIE_ART_LENGTH);
            move_right(DIE_ART_WIDTH + 1);
        }

        printf("\t");

        for (int j = 0; j < COLUMN; j++) {
            die* d = b2->grid[i][j];

            print_die(d);

            move_up(DIE_ART_LENGTH);
            move_right(DIE_ART_WIDTH + 1);
        }



        move_down(DIE_ART_LENGTH - 1);
        printf("\n");
    }
}



const char* die_1[5] = {
    "+-------+", "|       |", "|   O   |", "|       |", "+-------+",
};
const char* die_2[5] = {
    "+-------+", "| O     |", "|       |", "|     O |", "+-------+",
};
const char* die_3[5] = {
    "+-------+", "| O     |", "|   O   |", "|     O |", "+-------+",
};
const char* die_4[5] = {
    "+-------+", "| O   O |", "|       |", "| O   O |", "+-------+",
};
const char* die_5[5] = {
    "+-------+", "| O   O |", "|   O   |", "| O   O |", "+-------+",
};
const char* die_6[5] = {
    "+-------+", "| O   O |", "| O   O |", "| O   O |", "+-------+",
};
const char* die_empty[5] = {
    "+-------+", "|       |", "|       |", "|       |", "+-------+"
};
