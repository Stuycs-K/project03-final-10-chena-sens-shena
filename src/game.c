#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "../include/networking.h"
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
void awardPoints(struct player* p,char* guess, char* ans) { //player array, specific player index in array
    if (checkAnswer(guess,ans)==0) {
        printf("That is correct! Awarding 5 points to player %s\n",p->name);
        int prev = p->points;
        p->points = prev+5; //5 points for every correct guess 
        printf("That player's current points: %d\n",p->points);
    }
}
void loop(struct player* p/*later shoudl take in nothing*/) {
    char read[1024];
    char song[256] = "Placeholder";
    while (1) { //keep askign for input, 1s delay b/t guesses
        //reset song here (will change every guess)
        userInput(read);
        //reads guesses of each player and checks them; find struct of that player here 
        awardPoints(p,read,song);
        sleep(1);
    }
}
void leaderboard(struct player **playerlist, int n) {
    // int len = sizeof(playerlist)/sizeof(struct player*);
    //put array into text file 
    //sort struct array
    //put into text file 
    //read from text file 
    printf("Array size: %d\n",n);
    for (int i = 0;i<n;i++) {
        printf("i: %d name: %s id: %d points: %d\n",i,playerlist[i]->name,playerlist[i]->id,playerlist[i]->points);

    }
    // int index[n];
    //simple substitution sort, using the index
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            if(playerlist[i]->points > playerlist[j]->points) { //compare thru the index
                struct player * temp=playerlist[i];    //and swap only the indices
                playerlist[i] = playerlist[j];
                playerlist[j] = temp;
            }
        }
    }
    printf("Sorted\n");
    for (int i = 0;i<n;i++) {
        printf("i: %d name: %s id: %d points: %d\n",i,playerlist[i]->name,playerlist[i]->id,playerlist[i]->points);

    }
    //2 players, change later

}
int main() {
    char string[256] ="Blank Space";
    char test[256] ="Test";
    struct player *playerlist[2];
    struct player *t = malloc(sizeof(struct player));
    strcpy(t->name,"Amber");
    t->id = 1; //random number chosen
    t->points = 20;
    playerlist[0] = t;
    struct player *t1 = malloc(sizeof(struct player));
    strcpy(t1->name,"Anthony");
    t1->id = 1; //random number chosen
    t1->points = 15;
    playerlist[1] = t1;
    
    struct player *t2 = malloc(sizeof(struct player));
    strcpy(t2->name,"Shaurya");
    t2->id = 1; //random number chosen
    t2->points = 5;
    playerlist[2] = t2;
    leaderboard(playerlist,3);
    // strcpy()
    // loop(t);
}
