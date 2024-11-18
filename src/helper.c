#include "helper.h"

int get_int_range(char *prompt, int from, int to) {
    int input;
    char c=0;
    int valid = 0;
    do {
        printf("%s", prompt);
        if (scanf("%d%c", &input, &c) != 2 || c != '\n' || input < from ||
            input > to) {
            clear_buffer();
            printf("Invalid input. Please try again.\n");
        } else {
            valid = 1;
        }
    } while (!valid);
    return input;
}
