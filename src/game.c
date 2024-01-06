#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
//Get user input for guess, with 1s cooldown between guesses (no server)'''
//guesses are lowercase: add this note to directiosn in the beginning later

void userInput(char* returnString) {
    char line[1024];
    printf("Guess: ");
    fflush(stdout);
    fflush(stdin);
    fgets(line,sizeof(line),stdin);
    strcpy(returnString,line);
    printf("Read: %s\n",line); //this doesn't accurately test it, but alr tested prev in main
}
void convertLower(char* string) {
    for (int i = 0;string[i];i++) {
        string[i] = tolower(string[i]);
    }
}
int checkAnswer(char* guess, char* ans) {
    convertLower(ans); //convert song title to all lowercase
    printf("Guess: %s, Ans: %s\n",guess,ans);
    // printf("Converted lower: %s\n",ans);
    int answer = strcmp(guess,ans);  //same 
    // printf("Compare result: %d\n",answer);
    return answer;
}
void loop() {
    char read[1024];
    char song[256] = "Placeholder";
    while (1) { //keep askign for input, 1s delay b/t guesses
        userInput(read);
        // song = "Placeholder"; //get song name from array later
        int compare = checkAnswer(read,song);
        printf("Compare result: %d\n",compare);
        if (checkAnswer(read,song)==0) {
            printf("That is correct!");
        }
        sleep(1);
    }
}
int main() {
    // char read[1024];
    // loop();
    char string[256] ="Blank Space";
    char test[256] ="Test";
    // convertLower(string);
    loop();
    // printf("checkanswer: %d\n",checkAnswer(string,test));
    // printf("%s\n",string);
    // convertLower(hi);
}
