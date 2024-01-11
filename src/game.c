#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "../include/utils.h"
//Get user input for guess, with 1s cooldown between guesses (no server)'''
//guesses are lowercase: add this note to directiosn in the beginning later

void userInput(char* returnString) {
    char line[1024];
    printf("Guess: ");
    fflush(stdout);
    fflush(stdin);
    fgets(line,sizeof(line),stdin);
    strcpy(returnString,line);
    printf("Read: %s\n",returnString);
}
void convertLower(char* string) {
    for (int i = 0;string[i];i++) {
        string[i] = tolower(string[i]);
    }
}
int checkAnswer(char* guess, char* ans) {
    convertLower(ans); //convert song title to all lowercase
    guess[strcspn(guess, "\n")] = 0; //remove the newline from the end of the guess when they press enter
    int answer = strcmp(guess,ans);  //same
    return answer;
}
void leaderboard(struct player *playerlist, int n) {
    //sort the players by score
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            if(playerlist[i].points < playerlist[j].points) { //compare thru the index
                struct player temp=playerlist[i];    //and swap only the indices
                playerlist[i] = playerlist[j];
                playerlist[j] = temp;
            }
        }
    }
    printf("LEADERBOARD: \n");
    for (int i = 0;i<n;i++) {
        printf("%d. %s (id: %d): %d\n",i+1,playerlist[i].name,playerlist[i].id,playerlist[i].points);

    }
    //2 players, change later

}
int awardPoints(struct player *playerlist,int n,int playerid,char* guess, char* ans) { //player array, specific player index in array
    if (checkAnswer(guess,ans)==0) {
      for (int i = 0;i<n;i++) {
          if (playerlist[i].id==playerid) { //player whos score u want to update
            printf("That is correct! Awarding 5 points to player %s\n",playerlist[i].name);
            playerlist[i].points +=5;
            printf("Changing %s's (id: %d) score (previous: %d) to %d\n",playerlist[i].name,playerid,playerlist[i].points-5,playerlist[i].points);
            return 1;
          }
      }
      // leaderboard(playerlist,n);
    }
    return 0;
}
void game(struct player *playerlist,int n) {

    char* songs[] = { "assets/cooler.mp3", "assets/replay.mp3"};
    char read[1024];
    while (1) { //keep  playing songs

        int size = sizeof(songs) / sizeof(songs[0]);

        char* song = random_song(songs, size);
        play_song(song);
        // REMOVE SONGS

        //keep askign for input, 1s delay b/t guesses
        //reset song here (will change every guess)

        //get song struct here
        //name = song.name;

        int guessed = 0;
        while (guessed==0) {
          //read the [first response from a client] ([]: add in)
          userInput(read);
          //[get id of that client]
          int id = 1; //use id of player
          //reads guess of that player and checks them + displays leaderboard
          guessed = awardPoints(playerlist, n, id,read, song);
          // sleep(1); //[make the player with that id sleep] (client side after they send a message, not here)
        }
        printf("\n");
        leaderboard(playerlist,n);
        printf("\n");
        //start new song
    }
}
int main() {
    char string[256] ="Blank Space";
    char test[256] ="Test";
    struct player playerlist[2];
    struct player t;
    strcpy(t.name,"Amber");
    t.id = 1; //random number chosen
    t.points = 20;
    playerlist[0] = t;
    struct player t1;
    strcpy(t1.name,"Anthony");
    t1.id = 2; //random number chosen
    t1.points = 15;
    playerlist[1] = t1;

    struct player t2;
    strcpy(t2.name,"Shaurya");
    t2.id = 3; //random number chosen
    t2.points = 5;
    playerlist[2] = t2;
    leaderboard(playerlist,3);
    // updateScore(playerlist,3,3,50);

    struct player t3;
    strcpy(t3.name,"Carmin");
    t3.id = 3; //random number chosen
    t3.points = 14;
    playerlist[3] = t3;
    game(playerlist,4);
    // strcpy()
    // loop(t);
}
