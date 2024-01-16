#ifndef IMPORTS_H
#define IMPORTS_H

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PORT "19230"
#define BUFFER_SIZE 256

#define BOLD "\e[1m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define CLEAR "\e[0m"
#define ERASE "\e[A\e[K"

#define NAME_SIZE 256
#define MAX_PLAYERS 2 // CHANGE LATER
#define ROUND_DURATION 5

struct player
{
    int id;
    char name[NAME_SIZE];
    int points;
};

struct song
{
    char name[NAME_SIZE];
    char file_name[NAME_SIZE]; // mp3 file name
};

#endif
