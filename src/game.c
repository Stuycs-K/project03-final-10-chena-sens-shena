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
void loop() {
    char read[1024];
    while (1) { //keep askign for input, 1s delay b/t guesses
        userInput(read);
        sleep(1);
    }
}
void convertLower(char* string) {
    for (int i = 0;string[i];i++) {
        // printf("i: %d",i);
        string[i] = tolower(string[i]);
    }
}
int checkAnswer(char* guess, char* ans) {
    convertLower(ans); //convert song title to all lowercase
    return (strcmp(guess,ans)==0);  //same 
}
int main() {
    // char read[1024];
    // loop();
    char string[256] ="Hi";
    convertLower(string);
    printf("%s\n",string);
    // convertLower(hi);
}
