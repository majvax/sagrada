#include <stdio.h>
#include <time.h>


extern void move_up(int n);
extern void move_down(int n);
extern void move_left(int n);
extern void move_right(int n);
extern void clear();
extern void sleep(int ms);

extern int get_int_range(char* prompt, int from, int to);
extern void wait_for_enter();
