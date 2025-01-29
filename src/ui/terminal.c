#include "terminal.h"
#include <stdlib.h>

// Déplace le curseur vers le haut de n lignes
void move_up(int n) { printf("\033[%dA", n); }

// Déplace le curseur vers le bas de n lignes
void move_down(int n) { printf("\033[%dB", n); }

// Déplace le curseur vers la gauche de n colonnes
void move_left(int n) { printf("\033[%dD", n); }

// Déplace le curseur vers la droite de n colonnes
void move_right(int n) { printf("\033[%dC", n); }

// Efface l'écran
void clear(void) { printf("\033[H\033[J"); }

// Attend ms millisecondes
void sleep(int ms) {
    clock_t start = clock();
    while (clock() < start + ms);
}

// Demande un entier entre from et to
int get_int_range(char* prompt, int from, int to) {
    int choice = 0;
    do {
        char buffer[100];
        sprintf(buffer, prompt, from, to);
        printf("%s", buffer);
        scanf("%d", &choice);
    } while (choice < from || choice > to);
    return choice;
}

// Demande un nom à l'utilisateur, ne supporte pas les espaces
char* ask_for_name(char* prompt) {
    char* name = malloc(sizeof(char) * 100);
    printf("%s", prompt);
    scanf("%s", name);
    return name;
}

// Attend que l'utilisateur appuie sur Entrée
void wait_for_enter() {
    while (getchar() != '\n');
    getchar();
}
