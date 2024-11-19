#include "terminal.h"



void move_up(int n) { printf("\033[%dA", n); }

void move_down(int n) { printf("\033[%dB", n); }

void move_left(int n) { printf("\033[%dD", n); }

void move_right(int n) { printf("\033[%dC", n); }

void clear(void) { printf("\033[H\033[J"); }


int get_int_range(char* prompt, int from, int to) {
    int choice = 0;
    do {
        printf("%s", prompt);
        scanf("%d", &choice);
    } while (choice < from || choice > to);
    return choice;
}
