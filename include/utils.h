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
  char file_name[NAME_SIZE]; //mp3 file name 
};
char * random_song(char** songs, int size) ;

void play_song(char *filename) ;


#endif
