#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//Get user input for guess, with 1s cooldown between guesses (no server)'''

void userInput(char* returnString) {
    while(1) {
        char line[1024];
        printf("Guess: ");
        fflush(stdout);
        fflush(stdin);
        fgets(line,sizeof(line),stdin);
        strcpy(returnString,line);
        printf("Read: %s\n",line); //this doesn't accurately test it, but alr tested prev in main
        sleep(1);
    }
    // sleep(1);
}
int main() {
    char read[1024];
    // while(1) {
        userInput(read);
    //     printf("Read: %s\n",read);
    //     sleep(1);
    // }

}
