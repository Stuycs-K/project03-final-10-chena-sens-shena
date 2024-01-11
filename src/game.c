#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "../include/utils.h"
// Get user input for guess, with 1s cooldown between guesses (no server)'''
// guesses are lowercase: add this note to directiosn in the beginning later

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

void game()
{
    struct song songs[] = {
        {"Cooler Than Me", "assets/c.mp3"},
        {"Replay", "assets/r.mp3"}};
    int total_songs = sizeof(songs) / sizeof(songs[0]);

    struct song *played_songs = malloc(total_songs * sizeof(struct song));
    int total_played_songs = 0;

    // game loop
    while (total_played_songs < total_songs)
    {

        // pick random song and add song to played songs
        struct song cur_song = random_song(songs, total_songs, played_songs, total_played_songs);
        printf("Song Name: %s\n", cur_song.name);
        printf("File Name: %s\n", cur_song.file_name);
        // play_song(cur_song.file_name); // MOVE TO SERVER
        played_songs[total_played_songs] = cur_song;
        total_played_songs++;

        // prompt user for input
        char read[1024];

        // TODO: get player id and award points to specific player

        int guessed = 0;
        while (!guessed)
        {
            printf("Enter your guess: ");
            fgets(read, 1024, stdin);

            if (checkAnswer(read, cur_song.name) == 0)
            {
                printf("correct answer!\n");
                guessed = 1;
            }
            // keep reading from next player's guess
        }
    }
}

int main()
{

    // char string[256] ="Blank Space";
    // char test[256] ="Test";
    // struct player playerlist[2];
    // struct player t;
    // strcpy(t.name,"Amber");
    // t.id = 1; //random number chosen
    // t.points = 20;
    // playerlist[0] = t;
    // struct player t1;
    // strcpy(t1.name,"Anthony");
    // t1.id = 2; //random number chosen
    // t1.points = 15;
    // playerlist[1] = t1;

    // struct player t2;
    // strcpy(t2.name,"Shaurya");
    // t2.id = 3; //random number chosen
    // t2.points = 5;
    // playerlist[2] = t2;
    // leaderboard(playerlist,3);
    // // updateScore(playerlist,3,3,50);

    // struct player t3;
    // strcpy(t3.name,"Carmin");
    // t3.id = 3; //random number chosen
    // t3.points = 14;
    // playerlist[3] = t3;
    // game(playerlist,4);
    // strcpy()
    // loop(t);

    game();
}
