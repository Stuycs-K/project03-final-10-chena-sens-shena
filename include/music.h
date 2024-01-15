#ifndef MUSIC_H
#define MUSIC_H

#include "imports.h"
#include "networking.h"
#include "utils.h"

int play_song(char *filename);
int song_used(char *songName, struct song *played_songs, int total_played_songs);
struct song random_song(struct song *songs, int total_songs, struct song *played_songs, int total_played_songs);

#endif
