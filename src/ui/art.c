#include "art.h"

const char** get_ascii_die(struct die* d) {
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

void print_die(struct die* d) {
    char* color = (d != NULL) ? get_ansi_code(d->color) : ANSI_RESET;
    const char** art = get_ascii_die(d);

    for (int k = 0; k < DIE_ART_LENGTH; k++) {
        printf("%s%s%s ", color, art[k], ANSI_RESET);
        move_left(DIE_ART_WIDTH + 1);
        move_down(1);
    }
}

void print_dice(struct die** dice, int size) {
    int nb_dice = 0;
    for (int i = 0; i < size; i++) {
        if (dice[i] != NULL)
            printf("    %d      ", ++nb_dice);
    }
    printf("\n");
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

void print_boards(struct board* b, struct board* b2) {

    // Print Column indice numbers
    printf("\t");
    for (int i = 1; i < COLUMN+1; i++) {
        for (int j = 0; j < DIE_ART_WIDTH/2; j++) {
            printf(" ");
        }
        printf("%d", i);
        for (int j = 0; j < DIE_ART_WIDTH/2+1; j++) {
            printf(" ");
        }
    }
    printf("\t");
    for (int i = 1; i < COLUMN+1; i++) {
        for (int j = 0; j < DIE_ART_WIDTH/2; j++) {
            printf(" ");
        }
        printf("%d", i);
        for (int j = 0; j < DIE_ART_WIDTH/2+1; j++) {
            printf(" ");
        }
    }
    printf("\n");



    for (int i = 0; i < ROW; i++) {
        printf("\t");
        // Print Row indice numbers
        move_left(2);
        move_down(DIE_ART_LENGTH/2);
        printf("%d ", i+1);
        move_up(DIE_ART_LENGTH/2);

        for (int j = 0; j < COLUMN; j++) {
            struct die* d = b->grid[i][j];

            print_die(d);

            move_up(DIE_ART_LENGTH);
            move_right(DIE_ART_WIDTH + 1);
        }

        printf("\t");

        for (int j = 0; j < COLUMN; j++) {
            struct die* d = b2->grid[i][j];

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
