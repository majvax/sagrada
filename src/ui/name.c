#include "name.h"
#include <stdlib.h>




char* names[NUMBER_OF_NAMES] = {
    "Emma",
    "Louise",
    "Alice",
    "Chloe",
    "Lea",
    "Manon",
    "Camille",
    "Sarah",
    "Juliette",
    "Charlotte",
    "Ines",
    "Sophie",
    "Marie",
    "Claire",
    "Lucie",
    "Lucas",
    "Louis",
    "Gabriel",
    "Jules",
    "Hugo",
    "Arthur",
    "Adam",
    "Leo",
    "Paul",
    "Nathan",
    "Thomas",
    "Victor",
    "Antoine",
    "Maxime",
    "Raphael"
};


char* get_random_name(void) {
    return names[rand() % NUMBER_OF_NAMES];
}
