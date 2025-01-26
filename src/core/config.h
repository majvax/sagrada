#ifndef CONFIG_H
#define CONFIG_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CONFIG_FILE "config.txt"

struct Config {
    int simulations;
    int nocolors;
    int difficulty;
};


extern int init_config(const char* filepath);
extern const struct Config* get_config(void);
extern void free_config(void);
extern void print_config(void);



#endif // CONFIG_H
