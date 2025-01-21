#include "config.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define OPTION_WIDTH 30


struct Argument {
    const char* arg;
    const char* value;
    int boolean_value;
};


extern int parse_args(int argc, char* argv[]);
