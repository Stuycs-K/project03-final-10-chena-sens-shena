#ifndef GAME_H
#define GAME_H

#include "imports.h"

void user_input(char *returnString);
void convert_lower(char *string);
int check_answer(char *guess, char *ans);
void leaderboard(struct player *playerlist, int n);
int award_point(struct player *playerlist, int n, int playerid, char *guess, char *ans);
int guessing(struct player *players, char *song_name);
void initialize_game(struct player *players);
void play_random_song();
void game(struct player *playerlist, int n);
int sizeofArray(struct player *players);

#endif
