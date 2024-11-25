#include "board.h"
#include "terminal.h"
#include <stdio.h>


board* create_board() {
    // allocate 160 bytes for the board
    board* b = malloc(sizeof(board));
    assert(b != NULL && "create_board: Memory allocation failed");

    // initiate every dice to NULL
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            b->grid[i][j] = NULL;

    return b;
}

board* copy_board(board* b) {
    board* copy = create_board();
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            if (b->grid[i][j] != NULL)
                copy->grid[i][j] = create_die(b->grid[i][j]->color, b->grid[i][j]->value);
            else
                copy->grid[i][j] = NULL; // should be NULL anyway
    return copy;
}

void free_board(board* b) {
    if (b == NULL)
        return;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (b->grid[i][j] != NULL) {
                free_die(b->grid[i][j]);
                b->grid[i][j] = NULL;
            }
        }
    }
    free(b);
}

int place_die(board* b, die* d, int posx, int posy) {
    if (posx < 0 || posx >= ROW || posy < 0 || posy >= COLUMN)
        return 0;
    if (b->grid[posx][posy] != NULL)
        return 0;
    b->grid[posx][posy] = create_die(d->color, d->value);
    return 1;
}

int calculate_row(board* b, int row) {
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

    // extra rule (if 5 dice in a row are different value -> 5pts, and if they are same color -> 10pts)
    if (EXTRA_RULES &&
        b->grid[row][0]->color == b->grid[row][1]->color &&
        b->grid[row][1]->color == b->grid[row][2]->color &&
        b->grid[row][2]->color == b->grid[row][3]->color &&
        b->grid[row][3]->color == b->grid[row][4]->color)
        return 10;
    return 5;
}

int calculate_column(board* b, int column) {
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

    // extra rule (if 4 dice in a column are different colors -> 5pts, and if they are same value -> 10pts)
    if (EXTRA_RULES &&
        b->grid[0][column]->value == b->grid[1][column]->value &&
        b->grid[1][column]->value == b->grid[2][column]->value &&
        b->grid[2][column]->value == b->grid[3][column]->value)
        return 10;

    return 5;
}

int calculate_points(board* b) {
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
