#include "color.h"

char* get_ansi_code(int color) {
    switch (color) {
    case BLUE:
        return ANSI_BLUE;
    case YELLOW:
        return ANSI_YELLOW;
    case RED:
        return ANSI_RED;
    case GREEN:
        return ANSI_GREEN;
    case PURPLE:
        return ANSI_PURPLE;
    default:
        return "";
    }
}

int get_color_code(char c) {
    switch (c) {
    case 'b':
        return BLUE;
    case 'y':
        return YELLOW;
    case 'r':
        return RED;
    case 'g':
        return GREEN;
    case 'p':
        return PURPLE;
    default:
        return -1;
    }
}

char* get_background_color_code(int color) {
    switch (color) {
    case 'b':
        return BACKGROUND_BLUE;
    case 'y':
        return BACKGROUND_YELLOW;
    case 'r':
        return BACKGROUND_RED;
    case 'g':
        return BACKGROUND_GREEN;
    case 'p':
        return BACKGROUND_PURPLE;
    default:
        return "";
    }
}
