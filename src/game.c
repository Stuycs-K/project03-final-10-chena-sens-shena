#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//Get user input for guess, with 1s cooldown between guesses (no server)'''

void userInput(char* returnString) {
    //size of line is always 8 bcuz pointer
    char line[1024];
    printf("Guess: ");
    fflush(stdout);
    fflush(stdin);
    // printf("Sizeof line: %d",sizeof(line));
    fgets(line,sizeof(line),stdin);
    // fflush(stdout);
    // fflush(stdin);
    strcpy(returnString,line);
    // printf("Read: %s\n",line);
    // return line;
    //sleep(1);
}
int main() {
    // char line[1024];
    char read[1024];
    while(1) {
        // printf("SIZE OF LINE: %d",sizeof(line));
        userInput(read);
        printf("Read: %s\n",read);
    }

}
