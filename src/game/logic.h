#include "board.h"
#include "art.h"
#include "bot.h"

extern void player_turn(board* b, die** dice, int dice_left);
extern void bot_turn(board* b, board* player_board, die** dice, die** dice_set, int rounds_remaining, int priority);
extern void round_menu(int rounds, board* player_board, board* bot_board, die** dice);
extern void play_round(int rounds, die** dice_set, board* player_board, board* bot_board, int priority);
extern void play_game(board* player_board, board* bot_board, die** dice_set);
