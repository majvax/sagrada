#include "config.h"


struct Config* config = NULL;


void create_config_file(const char* filepath) {
    FILE* file = fopen(filepath, "w");

    if (file == NULL) {
        return;
    }

    fprintf(file, "simulations=1000\n");
    fclose(file);
}



void populate_config(struct Config* c) {
    if (c == NULL) {
        return;
    }
    c->simulations = 1000;
}


int init_config(const char* filepath) {
    if (config == NULL) {
        config = (struct Config*)malloc(sizeof(struct Config));
        populate_config(config);
    }

    FILE* file = fopen(filepath, "r");

    if (file == NULL) {
        create_config_file(filepath);
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* key = strtok(line, "=");
        char* value = strtok(NULL, "=");

        if (key == NULL || value == NULL) {
            continue;
        }


        if (strcmp(key, "simulations") == 0) {
            config->simulations = atoi(value);
        }
    }

    fclose(file);
    return 1;
}

const struct Config* get_config(void) { return config; }

void free_config(void) {
    if (config != NULL) {
        free(config);
        config = NULL;
    }
}


void print_config(void) {
    const struct Config* c = get_config();
    printf("simulations: %d\n", c->simulations);

    printf("\n\n  -> Appuyez sur 'entrer' pour acceder au menu\n");
}
