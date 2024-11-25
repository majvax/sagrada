#include "board.h"
#include "bot.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void player_turn(board* player_board, die** dice, int dice_left) {
    int choice = get_int_range("-> Choisissez un de (%d-%d): ", 1, dice_left);
    // decrement the choice to match the real index (if dice 1 and 2 are placed, the choice 1 will
    // be the 3rd dice)
    for (int i = 0; i < choice; i++)
        if (dice[i] == NULL)
            choice++;


    int x = get_int_range("-> Choisissez ou le placer (position x de %d a %d): ", 1, COLUMN);
    int y = get_int_range("-> Choisissez ou le placer (position y de %d a %d): ", 1, ROW);

    while (place_die(player_board, dice[choice - 1], y - 1, x - 1) == 0) {
        printf("-> Impossible de placer le de a cet endroit\n");
        x = get_int_range("-> Choisissez ou le placer (position x de %d a %d): ", 1, COLUMN);
        y = get_int_range("-> Choisissez ou le placer (position y de %d a %d): ", 1, ROW);
    }

    free_die(dice[choice - 1]);
    dice[choice - 1] = NULL;
}

void bot_turn(board* bot_board, board* player_board, die** dice, die** dice_set_copy,
              int rounds_remaining, int priority) {
    int dice_index =
        make_move(bot_board, dice, player_board, dice_set_copy, rounds_remaining, priority);
    free_die(dice[dice_index]);
    dice[dice_index] = NULL;
}

void round_menu(int rounds, board* player_board, board* bot_board, die** dice) {
    clear();
    printf("-> TOUR %d\n\n\n", rounds);
    print_boards(player_board, bot_board);
    printf("\n\n");
    printf("-> Votre score: %d\n-> Score adverse: %d\n\n", calculate_points(player_board),
           calculate_points(bot_board));
    printf("-> Voici les des de ce tour\n");
    print_dice(dice, 5);
    printf("\n");
}

void play_round(int rounds, die** dice_set, board* player_board, board* bot_board, int priority) {
    die** dice = get_dice(dice_set, 5);
    int dice_left = 5;
    int rounds_remaining = 11 - rounds;

    round_menu(rounds, player_board, bot_board, dice);



    // bot against bot for testing purposes
    // if (priority) {
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    // } else {
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(player_board, bot_board, dice, dice_set, rounds_remaining, priority);
    //     round_menu(rounds, player_board, bot_board, dice);
    //     bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
    // }

    // free_dice(dice, 5);
    // return;



    if (priority) {
        player_turn(player_board, dice, dice_left--);
        round_menu(rounds, player_board, bot_board, dice);
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
        round_menu(rounds, player_board, bot_board, dice);
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
        round_menu(rounds, player_board, bot_board, dice);
        player_turn(player_board, dice, dice_left--);
    } else {
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
        round_menu(rounds, player_board, bot_board, dice);
        player_turn(player_board, dice, dice_left--);
        round_menu(rounds, player_board, bot_board, dice);
        player_turn(player_board, dice, dice_left--);
        round_menu(rounds, player_board, bot_board, dice);
        bot_turn(bot_board, player_board, dice, dice_set, rounds_remaining, priority);
        dice_left--;
    }

    free_dice(dice, 5);
}

int main(void) {
    srand((unsigned)time(NULL));
    die** dice_set = create_dice_set();
    board* player_board = create_board(); // player's board
    board* bot_board = create_board();    // board of the bot
    int priority = rand() % 2;            // 0 or 1

    for (int rounds = 1; rounds < 11; rounds++) {
        play_round(rounds, dice_set, player_board, bot_board, priority);
        priority = !priority;
    }

    clear();
    print_boards(player_board, bot_board);
    printf("\n\n");
    printf("-> Votre score: %d\n-> Score adverse: %d\n\n", calculate_points(player_board),
           calculate_points(bot_board));

    if (calculate_points(player_board) > calculate_points(bot_board)) {
        printf("-> Vous avez gagne!\n");
    } else if (calculate_points(player_board) < calculate_points(bot_board)) {
        printf("-> Vous avez perdu!\n");
    } else {
        printf("-> Egalite!\n");
    }

    free_board(player_board);
    free_board(bot_board);
    free_dice(dice_set, DICE_SET_SIZE);
    return 0;
}
