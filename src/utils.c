#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



// int rand_int() {
//     int file = open("/dev/random", O_RDONLY);
//     int n;
//     int random_int = read(file ,&n, 4);
//     if (random_int==-1) exit(1);
//     if(n<0) {
//         n*=-1;
//     }
//     return n;

// }

void playSong(char *filename) {

    char* filename = "random.mp3";
    char* args[] = {"mpg123", filename, NULL};
    execvp("mpg123", args);
    return 0;

}

// char * random_song(char** songs) {

//     int size = len(songs);
//     int n =  (rand_int() % size ) ;

//     return songs[n];

// }
