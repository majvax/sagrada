#include "color.h"

// Retourne le code ANSI correspondant à la couleur
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
