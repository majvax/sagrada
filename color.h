#ifndef COLOR_H
#define COLOR_H


#define BLUE 0
#define YELLOW 1
#define RED 2
#define GREEN 3
#define PURPLE 4

#define ASCII_BLUE "\e[0;34m"
#define ASCII_YELLOW "\e[0;33m"
#define ASCII_RED "\e[0;31m"
#define ASCII_GREEN "\e[0;32m"
#define ASCII_PURPLE "\e[0;35m"


#define BACKGROUND_BLUE "\e[44m"
#define BACKGROUND_YELLOW "\e[43m"
#define BACKGROUND_RED "\e[41m"
#define BACKGROUND_GREEN "\e[42m"
#define BACKGROUND_PURPLE "\e[45m"


extern char* get_ascii_code(int color);
extern char* get_background_color_code(int color);
extern int get_color_code(char c);




#endif // COLOR_H
