#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include "../include/utils.h"
#include <string.h>



void userInput(char *returnString)
{
    char line[1024];
    printf("Guess: ");
    fflush(stdout);
    fflush(stdin);
    fgets(line, sizeof(line), stdin);
    strcpy(returnString, line);
    printf("Read: %s\n", returnString);
}
void convertLower(char *string)
{
    for (int i = 0; string[i]; i++)
    {
        string[i] = tolower(string[i]);
    }
}
int checkAnswer(char *guess, char *ans)
{
    convertLower(ans);               // convert song title to all lowercase
    guess[strcspn(guess, "\n")] = 0; // remove the newline from the end of the guess when they press enter
    int answer = strcmp(guess, ans); // same
    return answer;
}
void leaderboard(struct player *playerlist, int n)
{
    // sort the players by score
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (playerlist[i].points < playerlist[j].points)
            {                                       // compare thru the index
                struct player temp = playerlist[i]; // and swap only the indices
                playerlist[i] = playerlist[j];
                playerlist[j] = temp;
            }
        }
    }
    printf("LEADERBOARD: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s (id: %d): %d\n", i + 1, playerlist[i].name, playerlist[i].id, playerlist[i].points);
    }
    // 2 players, change later
}
int awardPoints(struct player *playerlist, int n, int playerid, char *guess, char *ans)
{ // player array, specific player index in array
    if (checkAnswer(guess, ans) == 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (playerlist[i].id == playerid)
            { // player whos score u want to update
                printf("That is correct! Awarding 5 points to player %s\n", playerlist[i].name);
                playerlist[i].points += 5;
                printf("Changing %s's (id: %d) score (previous: %d) to %d\n", playerlist[i].name, playerid, playerlist[i].points - 5, playerlist[i].points);
                return 1;
            }
        }
        // leaderboard(playerlist,n);
    }
    return 0;
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
