#ifndef COLOR_H
#define COLOR_H

#define BLUE 0
#define YELLOW 1
#define RED 2
#define GREEN 3
#define PURPLE 4

#define ANSI_RESET "\033[0m"
#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_PURPLE "\033[0;35m"

extern char* get_ansi_code(int color);

#endif // COLOR_H
