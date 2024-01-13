#ifndef MUSIC_H
#define MUSIC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "../include/utils.h"

struct song
{
  char name[NAME_SIZE];
  char file_name[NAME_SIZE]; //mp3 file name 
};

void play_song(char *filename);
int song_used(const char* songName, const struct song* played_songs, int total_played_songs);
struct song random_song(struct song* songs, int total_songs, struct song* played_songs, int total_played_songs);

#endif 
