#include "argparser.h"



int get_argument(struct Argument* arg, int argc, char* argv[], int index, int has_value) {
    if (index >= argc || (has_value && index + 1 >= argc) || argv == NULL) {
        return 0;
    }
    arg->arg = argv[index];
    arg->value = has_value ? argv[index + 1] : NULL;
    arg->boolean_value = !has_value;
    return 1;
}


void print_option(const char* option, const char* description) {
    printf("  %-*s %s\n", OPTION_WIDTH, option, description);
}


void print_args(void) {
    printf("Usage: ./sagrada.exe [options <argument>] ...\n");
    printf("Options:\n");
    print_option("-h", "Show this message");
    print_option("-c", "Disable colored output");
    print_option("--config <file>", "Specify a configuration file");
    print_option("--difficulty <difficulty>", "Set the difficulty level (1-5)");
    print_option("--simulations <simulations>", "Set the number of simulations to run");
}



int parse_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--config") == 0) {
            struct Argument arg;
            if (get_argument(&arg, argc, argv, i++, 1) && arg.value != NULL)
                init_config(arg.value);
        }
    }

    struct Config* config = get_mutable_config();
    struct Argument arg;

    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL) {
            continue;
        }

        if (strcmp(argv[i], "-h") == 0) {
            print_args();
            return 0;
        } else if (strcmp(argv[i], "--difficulty") == 0 &&
                   get_argument(&arg, argc, argv, i++, 1))
            config->difficulty = atoi(arg.value);
        else if (strcmp(argv[i], "--simulations") == 0 && get_argument(&arg, argc, argv, i++, 1))
            config->simulations = atoi(arg.value);
        else if (strcmp(argv[i], "-c") == 0)
            config->nocolors = 1;
        else {
            printf("-> Unknown option: %s\n", argv[i]);
            return 0;
        }
    }
    return 1;
}
