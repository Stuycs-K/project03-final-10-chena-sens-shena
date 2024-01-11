#ifndef UTILS_H
#define UTILS_H

#define NAME_SIZE 150
struct player
{
  int id;
  char name[NAME_SIZE];
  int points;
};

struct song
{
  char name[NAME_SIZE];
  char file_name[NAME_SIZE]; //mp3 file name 
};
struct song random_song(struct song* songs, int total_songs, struct song* played_songs, int total_played_songs);
int song_used(const char* songName, const struct song* played_songs, int total_played_songs);

void play_song(char *filename) ;


#endif
