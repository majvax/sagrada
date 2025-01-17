#ifndef CONFIG_H
#define CONFIG_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DEFAULT_CONFIG_FILE "config.txt"

struct Config {
    int simulations;
    bool nocolors;
    int difficulty;
};


extern bool init_config(const char* filepath);
extern const struct Config* get_config(void);
extern struct Config* get_mutable_config(void);
extern void free_config(void);
extern void print_config(void);



#endif // CONFIG_H
