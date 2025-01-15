#include "board.h"


struct board* create_board() {
    // allocate 160 bytes for the board
    struct board* b = malloc(sizeof(struct board));
    assert(b != NULL && "create_board: Memory allocation failed");

    // initiate every dice to NULL
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            b->grid[i][j] = NULL;

    return b;
}

struct board* copy_board(struct board* b) {
    struct board* copy = create_board();
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            if (b->grid[i][j] != NULL)
                copy->grid[i][j] = create_die(b->grid[i][j]->color, b->grid[i][j]->value);
            else
                copy->grid[i][j] = NULL; // should be NULL anyway
    return copy;
}

void free_board(struct board* b) {
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

bool place_die(struct board* b, struct die* d, int posx, int posy) {
    if (posx < 0 || posx >= ROW || posy < 0 || posy >= COLUMN)
        return false;
    if (b->grid[posx][posy] != NULL)
        return false;
    b->grid[posx][posy] = create_die(d->color, d->value);
    return true;
}

int calculate_row(struct board* b, int row) {
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

int calculate_column(struct board* b, int column) {
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

int calculate_points(struct board* b) {
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

