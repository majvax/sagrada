#include <stdio.h>


#define PRINT_AND_DIE_IF_COND_NOT_MEET(cond, message, exit_code) if(cond) { printf("%s\n", message); exit(exit_code); }
