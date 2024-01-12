#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include "../include/utils.h"
#include <string.h>




int rand_int() {
    int file = open("/dev/random", O_RDONLY);
    int n;
    int random_int = read(file ,&n, 4);
    if (random_int==-1) exit(1);
    if(n<0) {
        n*=-1;
    }
    return n;

}

void play_song(char *filename) {

    int p = fork();

    if (p == 0 ) {
        char* args[] = {"mpg123", "-q",  filename, NULL};
        execvp("mpg123", args);
    }    
    
}

int song_used(const char* songName, const struct song* played_songs, int total_played_songs) {
    for (int i = 0; i < total_played_songs; i++) {
        if (strcmp(songName, played_songs[i].name) == 0) {
            return 1; 
        }
    }
    return 0; 
}
    

struct song random_song(struct song* songs, int total_songs, struct song* played_songs, int total_played_songs) {
   int n =  (rand_int() % total_songs );
   // if the song is used keep rerolling
   while (song_used(songs[n].name, played_songs, total_played_songs)) {
       n = rand_int() % total_songs;
   }
   return songs[n];
}

// }
