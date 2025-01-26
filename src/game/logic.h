#include "board.h"
#include "art.h"
#include "bot.h"


struct Game {
    struct board* player_board;
    struct board* bot_board;
    struct die** dice_set;
    struct die** dice;
    int mode;
    char* player1;
    char* player2;
    int priority;
};

extern void player_turn(struct Game* game, struct board* board, int dice_left);
extern void bot_turn(struct Game* game, struct board* board1, struct board* board2, int rounds_remaining);
extern void round_menu(struct Game* game, int rounds, char* player_name);
extern void play_round(int rounds, struct die** dice_set, struct board* player_board, struct board* bot_board, int priority);
extern void play_game(struct Game* game);
extern int game_menu();
extern void print_rules();

extern void bot_against_bot(struct Game* game, int rounds);
extern void player_against_bot(struct Game* game, int rounds);
extern void player_against_player(struct Game* game, int rounds);
