#include <stdio.h>



extern int   get_int_range(char* prompt, int from, int to);
extern char  get_char(char* prompt);
extern char* get_string(char* prompt, char** valid);
extern void  clear_screen();
extern void  clear_buffer();
