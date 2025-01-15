#include "board.h"
#include "art.h"
#include "bot.h"

extern void player_turn(struct board* b, struct die** dice, int dice_left);
extern void bot_turn(struct board* b, struct board* player_board,struct die** dice, struct die** dice_set, int rounds_remaining, int priority);
extern void round_menu(int rounds, struct board* player_board,struct  board* bot_board, struct die** dice);
extern void play_round(int rounds, struct die** dice_set, struct board* player_board, struct board* bot_board, int priority);
extern void play_game(struct board* player_board, struct board* bot_board, struct die** dice_set);
extern void game_menu();
extern void print_rules();
