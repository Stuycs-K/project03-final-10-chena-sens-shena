#include "../include/game.h"

// Get user input for guess, with 1s cooldown between guesses (no server)'''
// guesses are lowercase: add this note to directiosn in the beginning later
void user_input(char *returnString)
{
    char line[1024];
    printf("Guess: ");
    fflush(stdout);
    fflush(stdin);
    fgets(line, sizeof(line), stdin);
    strcpy(returnString, line);
    printf("Read: %s\n", returnString);
}

void convert_lower(char *string)
{
    for (int i = 0; string[i]; i++)
    {
        string[i] = tolower(string[i]);
    }
}

int check_answer(char *guess, char *ans)
{
    convert_lower(ans);              // convert song title to all lowercase
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

int award_point(struct player *playerlist, int n, int playerid, char *guess, char *ans)
{ // player array, specific player index in array
    if (check_answer(guess, ans) == 0)
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

// int guessing(struct player *players, char *song_name);

// void initialize_game(struct player *players );

// void play_random_song();

void game(struct player *playerlist, int n)
{
    // // initialize_game() {
    // struct song songs[] = {
    //     {"Cooler Than Me", "assets/c.mp3"},
    //     {"Replay", "assets/r.mp3"}};
    // int total_songs = sizeof(songs) / sizeof(songs[0]);
    // struct song *played_songs = malloc(total_songs * sizeof(struct song));
    // int total_played_songs = 0;

    //     // play_random_song( ) {

    //     // pick random song and add song to played songs
    //     struct song cur_song = random_song(songs, total_songs, played_songs, total_played_songs);
    //     printf("Song Name (FOR TESTING): %s\n", cur_song.name);

    //     play_song(cur_song.file_name); // MOVE TO SERVER
    //     played_songs[total_played_songs] = cur_song;
    //     total_played_songs++;
    //     // }

    //     char read[1024]; // not needed

    //     // TODO: get player id

    //     int guessed = 0;
    //     while (guessed == 0)
    //     {
    //         // guessing {
    //         // guessed = guessing(playerlist, cur_song.name);
    //         // prompt players for guess, read the first player
    //         user_input(read);

    //         // id of first player to respond
    //         int id = 1; // placeholder id right now

    //         guessed = award_point(playerlist, n, id, read, cur_song.name);
    //         //}

    //         // keep reading from next player's guess if that guess wasn't correct
    //     }
    //     printf("\n");
    //     leaderboard(playerlist, n);
    //     printf("\n");
    // // }

    // printf("All Songs Completed!\n");
}
int sizeofArray(struct player *players)
{
    int n = 0;
    int i = 0;
    while (players[i].id != 0)
    {
        n++;
        i++;
    }
    return n;
}
int main()
{
    char string[256] = "Blank Space";
    char test[256] = "Test";
    struct player playerlist[2];
    struct player t;
    strcpy(t.name, "Amber");
    t.id = 1; // random number chosen
    t.points = 20;
    playerlist[0] = t;
    struct player t1;
    strcpy(t1.name, "Anthony");
    t1.id = 2; // random number chosen
    t1.points = 15;
    playerlist[1] = t1;

    struct player t2;
    strcpy(t2.name, "Shaurya");
    t2.id = 3; // random number chosen
    t2.points = 5;
    playerlist[2] = t2;
    // leaderboard(playerlist,3);
    // updateScore(playerlist,3,3,50);

    struct player t3;
    strcpy(t3.name, "Carmin");
    t3.id = 3; // random number chosen
    t3.points = 14;
    playerlist[3] = t3;

    printf("%d\n", sizeofArray(playerlist));
    // game(playerlist, 4);
    // strcpy()
    // loop(t);
}
