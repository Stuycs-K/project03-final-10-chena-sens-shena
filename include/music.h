#ifndef MUSIC_H
#define MUSIC_H

#include "imports.h"
#include "utils.h"

void play_song(char *filename);
int song_used(const char *songName, const struct song *played_songs, int total_played_songs);
struct song random_song(struct song *songs, int total_songs, struct song *played_songs, int total_played_songs);

#endif
