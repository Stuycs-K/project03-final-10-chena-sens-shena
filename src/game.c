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
void loop() {
    char read[1024];
    char song[256] = "Placeholder";
    while (1) { //keep askign for input, 1s delay b/t guesses
        userInput(read);
        // song = "Placeholder"; //get song name from array later
        int compare = checkAnswer(read,song);
        // printf("Compare result: %d\n",compare);
        if (checkAnswer(read,song)==0) {
            printf("That is correct!\n");
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
