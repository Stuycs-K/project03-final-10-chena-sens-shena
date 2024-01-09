#ifndef UTILS_H
#define UTILS_H
struct player {
  int id;
  char name[15];
  int points;
};

void playMP3(const char *filename);


char * random_song(char** songs);



#endif