#ifndef CONFIG_H
#define CONFIG_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_CONFIG_FILE "config.txt"

typedef struct {
    int simulations;
    bool nocolors;
    int difficulty;
} Config;


extern bool init_config(const char* filepath);
extern const Config* get_config(void);
extern Config* get_mutable_config(void);
extern void free_config(void);
extern void print_config(void);




#endif // CONFIG_H
