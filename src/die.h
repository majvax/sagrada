#include <stdlib.h>
#include <assert.h>


typedef struct {
    int value;
    int color;
    int is_used;
} die;


extern die* create_die(int color, int value);
extern void free_die(die* d);

extern die** get_dice_set();
extern void free_dice_set(die** dice_set);
extern die** copy_dice_set(die** dice_set);
extern die* get_random_die(die** dice_set);

extern die** get_dice(die** dice_set, int number);
extern void free_dice(die** dice_set, int size);
