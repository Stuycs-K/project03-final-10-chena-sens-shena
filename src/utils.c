#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/fcntl.h>
#include "../include/utils.h"
#include "../include/game.h"

#include "../include/music.h"

#include <string.h>


void convertLower(char *string)
{
    for (int i = 0; string[i]; i++)
    {
        string[i] = tolower(string[i]);
    }
}

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



// }
