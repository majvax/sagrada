#include "config.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define OPTION_WIDTH 30


struct Argument {
    const char* arg;
    const char* value;
    bool boolean_value;
};


extern bool parse_args(int argc, char* argv[]);
