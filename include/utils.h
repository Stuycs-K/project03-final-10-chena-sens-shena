#ifndef UTILS_H
#define UTILS_H

#define NAME_SIZE 15
struct player
{
  int id;
  char name[NAME_SIZE];
  int points;
};

struct song
{
  char name[NAME_SIZE];
  char artist[NAME_SIZE];
  char file[NAME_SIZE]; //mp3 file name 
};
void playMP3(const char *filename);

char *random_song(char **songs);

#endif
