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

#define BACKGROUND_RED "\033[41m"
#define BACKGROUND_GREEN "\033[42m"
#define BACKGROUND_YELLOW "\033[43m"
#define BACKGROUND_BLUE "\033[44m"
#define BACKGROUND_PURPLE "\033[45m"

extern char* get_ansi_code(int color);
extern char* get_background_color_code(int color);
extern int get_color_code(char c);

#endif // COLOR_H
