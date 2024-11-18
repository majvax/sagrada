#include "board.h"
#include <stdio.h>

board *create_board() {
    board *b = malloc(sizeof(board));
    assert(b != NULL && "create_board: Memory allocation failed");

    // initiate every dice to NULL
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            b->grid[i][j] = NULL;

    b->score = 0;
    b->prediction = 0;

    return b;
}

void free_board(board *b) {
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            if (b->grid[i][j] != NULL)
                free(b->grid[i][j]);

    free(b);
}

int place_die(board *b, die *d, int posx, int posy) {
    if (b->grid[posx][posy] != NULL)
        return 0;
    die *nd = malloc(sizeof(die));
    assert(nd != NULL && "place_die: Memory allocation failed.");
    nd->color = d->color;
    nd->value = d->value;
    b->grid[posx][posy] = nd;

    return 1;
}

int calculate_row(board *b, int row) {
    for (int i = 0; i < COLUMN; i++) {
        if (b->grid[row][i] == NULL)
            return 0;
        int value = b->grid[row][i]->value;
        for (int j = i + 1; j < COLUMN; j++) {
            if (b->grid[row][j] == NULL)
                return 0;
            if (value == b->grid[row][j]->value)
                return 0;
        }
    }
    return 5;
}

int calculate_column(board *b, int column) {
    for (int i = 0; i < ROW; i++) {
        if (b->grid[i][column] == NULL)
            return 0;
        int color = b->grid[i][column]->color;
        for (int j = i + 1; j < ROW; j++) {
            if (b->grid[j][column] == NULL)
                return 0;
            if (color == b->grid[j][column]->color)
                return 0;
        }
    }
    return 5;
}

int calculate_points(board *b) {
    int score = 0;
    for (int i = 0; i < ROW; i++)
        score += calculate_row(b, i);

    for (int i = 0; i < COLUMN; i++)
        score += calculate_column(b, i);

    // calculate purple points
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            if (b->grid[i][j] != NULL && b->grid[i][j]->color == PURPLE)
                score += b->grid[i][j]->value;

    // TODO: calculate set of 5 dice for 4 pts

    return score;
}

void print_board(board *b) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            die *d = b->grid[i][j];
            if (d == NULL) {
                printf(" ");
                continue;
            }

            printf("%s%d", get_ascii_code(d->color), d->value);
            printf("\e[0m ");
        }
        printf("\n");
    }
}
