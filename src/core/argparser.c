#include "argparser.h"


typedef struct {
    const char* arg;
    const char* value;
    bool boolean_value;
} Argument;



bool get_argument(Argument* arg, int argc, char* argv[], int index, bool has_value) {
    if (index >= argc || (has_value && index + 1 >= argc) || argv == NULL) {
        return false;
    }
    arg->arg = argv[index];
    arg->value = has_value ? argv[index + 1] : NULL;
    arg->boolean_value = !has_value;
    return true;
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



bool parse_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--config") == 0) {
            Argument arg;
            if (get_argument(&arg, argc, argv, i++, true) && arg.value != NULL)
                init_config(arg.value);
        }
    }

    Config* config = get_mutable_config();
    Argument arg;

    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL) {
            continue;
        }

        if (strcmp(argv[i], "-h") == 0) {
            print_args();
            return false;
        } 
        else if (strcmp(argv[i], "--difficulty") == 0 && get_argument(&arg, argc, argv, i++, true))
            config->difficulty = atoi(arg.value);
        else if (strcmp(argv[i], "--simulations") == 0 && get_argument(&arg, argc, argv, i++, true))
            config->simulations = atoi(arg.value);
        else if (strcmp(argv[i], "-c") == 0)
            config->nocolors = true;
        else {
            printf("-> Unknown option: %s\n", argv[i]);
            return false;
        }
    }
    return true;
}
