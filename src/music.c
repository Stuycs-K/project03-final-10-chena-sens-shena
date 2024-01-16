#include "../include/music.h"

int play_song(char *filename)
{
    clear_stack();
    
    int p = fork();

    if (p == 0)
    {
        char *args[] = {"mpg123", "-q", filename, NULL};
        err(execvp("mpg123", args), "execvp error");

        exit(0);
    }

    return p;
}

int song_used(char *songName, struct song *played_songs, int total_played_songs)
{
    clear_stack();
    
    for (int i = 0; i < total_played_songs; i++)
        if (strcmp(songName, played_songs[i].name) == 0)
            return 1;

    return 0;
}

struct song random_song(struct song *songs, int total_songs, struct song *played_songs, int total_played_songs)
{
    clear_stack();
    
    int n = (rand_int() % total_songs);

    // if the song is used keep rerolling
    while (song_used(songs[n].name, played_songs, total_played_songs))
        n = rand_int() % total_songs;

    return songs[n];
}
