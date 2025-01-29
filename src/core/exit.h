#include <stdio.h>

// Macro qui vérifie une condition et affiche un message d'erreur si elle n'est pas respectée + termine le programme
// Utilisé pour les erreurs fatales (ex: allocation de mémoire échouée)
#define PRINT_AND_DIE_IF_COND_NOT_MEET(cond, message, exit_code) if(cond) { printf("%s\n", message); exit(exit_code); }
