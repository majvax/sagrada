#include "board.h"

struct board* create_board() {
    // allocate 160 bytes for the board
    struct board* b = malloc(sizeof(struct board));
    PRINT_AND_DIE_IF_COND_NOT_MEET(b == NULL, "create_board: Memory allocation failed", 1);

    // initiate every dice to NULL
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++)
            b->grid[i][j] = NULL;


    b->first_die_placed = 0;
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

int placeable(struct board* b, int posx, int posy) {
    if (posx < 0 || posx >= ROW || posy < 0 || posy >= COLUMN)
        return 0;

    if (b->grid[posx][posy] != NULL)
        return 0;

    if (!b->first_die_placed)
        return 1;

    if ((posx > 0 && b->grid[posx - 1][posy] != NULL) ||  // Check above
        (posx < ROW - 1 && b->grid[posx + 1][posy] != NULL) ||  // Check below
        (posy > 0 && b->grid[posx][posy - 1] != NULL) ||  // Check left
        (posy < COLUMN - 1 && b->grid[posx][posy + 1] != NULL)) {  // Check right
        return 1;  // Valid placement
    }

    return 0;
}

int place_die(struct board* b, struct die* d, int posx, int posy) {
    if (posx < 0 || posx >= ROW || posy < 0 || posy >= COLUMN)
        return 0;

    if (b->grid[posx][posy] != NULL)
        return 0;
        
    if (b->first_die_placed) {
        if ((posx > 0 && b->grid[posx - 1][posy] != NULL) ||  // Check above
            (posx < ROW - 1 && b->grid[posx + 1][posy] != NULL) ||  // Check below
            (posy > 0 && b->grid[posx][posy - 1] != NULL) ||  // Check left
            (posy < COLUMN - 1 && b->grid[posx][posy + 1] != NULL)) {  // Check right
            // At least one adjacent die exists, proceed to place the die
        } else {
            return 0;  // No adjacent die, placement is invalid
        }
    }

    b->grid[posx][posy] = create_die(d->color, d->value);
    b->first_die_placed = 1;
    return 1;
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

    return 5;
}

int stack_of_5(struct board* b) {
    int color_count[5] = {0};

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (b->grid[i][j] != NULL) {
                int color = b->grid[i][j]->color;
                if (color >= 0 && color < 5) {
                    color_count[color]++;
                }
            }
        }
    }

    int sets_of_5 = color_count[0];
    for (int i = 1; i < 5; i++) {
        if (color_count[i] < sets_of_5) {
            sets_of_5 = color_count[i];
        }
    }

    return sets_of_5;
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

    // calculate stack of 5 points for 4 pts each
    score += stack_of_5(b) * 4;


    return score;
}
