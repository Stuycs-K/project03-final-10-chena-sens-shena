#include "../include/game.h"
#include "../include/imports.h"
#include "../include/music.h"
#include "../include/networking.h"
#include "../include/utils.h"

void handle_new_client(int listen_socket, struct player *players)
{
    char name[NAME_SIZE];

    int client_socket = server_tcp_handshake(listen_socket);
    err(client_socket, "client accept error");

    read(client_socket, name, sizeof(name));
    printf(GREEN BOLD ">>> %s joined <<<\n" CLEAR, name);

    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id == 0)
        {
            players[i].id = client_socket;
            strcpy(players[i].name, name);
            break;
        }
}

void disconnect(int client_socket, int index, struct player *players)
{
    printf(RED BOLD ">>> %s left <<<\n" CLEAR, players[index].name);

    close(client_socket);
    players[index].id = 0;
}

void handle_client(fd_set read_fds, struct player *players) // also take in song name
{
    char msg[BUFFER_SIZE];
    for (int i = 0; i < MAX_PLAYERS; ++i)
    {
        int client_socket = players[i].id;
        if (FD_ISSET(client_socket, &read_fds))
        {
            if (read(client_socket, msg, sizeof(msg)))
            {

                write_all(msg, i, players);
                // award_points(players,MAX_PLAYERS,client_socket,msg,ans);
            }
            else
                disconnect(client_socket, i, players);
        }
    }
}

void server_listen(int listen_socket, fd_set read_fds, struct player *players)
{
    FD_ZERO(&read_fds);
    FD_SET(listen_socket, &read_fds);

    int max_socket = listen_socket;

    for (int i = 0; i < MAX_PLAYERS; ++i)
    {
        int client_socket = players[i].id;

        if (client_socket > 0)
            FD_SET(client_socket, &read_fds);

        if (client_socket > max_socket)
            max_socket = client_socket;
    }

    err(select(max_socket + 1, &read_fds, NULL, NULL, NULL), "select error");

    if (FD_ISSET(listen_socket, &read_fds))
        handle_new_client(listen_socket, players);

    handle_client(read_fds, players);
}

int main()
{
    // setup
    int listen_socket = server_setup();
    fd_set read_fds;
    struct player players[MAX_PLAYERS];

    struct song songs[] = {
        {"Cooler Than Me", "assets/c.mp3"},
        {"Replay", "assets/r.mp3"}};
    int total_songs = sizeof(songs) / sizeof(songs[0]);
    struct song played_songs[total_songs];
    int total_played_songs = 0;

    struct timeval start_time, current_time;
    gettimeofday(&start_time, NULL);

    while (1)
    {
        server_listen(listen_socket, read_fds, players); // blocks until something happens

        gettimeofday(&current_time, NULL);
        double elapsed_time = difftime(start_time.tv_sec, current_time.tv_sec);

        if (elapsed_time > ROUND_DURATION)
        {

            // game end things
            // show leaderboard
            // new song
            struct song cur_song = random_song(songs, total_songs, played_songs, total_played_songs);
            printf("Song Name (FOR TESTING): %s\n", cur_song.name);

            play_song(cur_song.file_name); // MOVE TO SERVER
            played_songs[total_played_songs] = cur_song;
            total_played_songs++;

            // handle_client(read_fds, players);
            // reset start time
            gettimeofday(&start_time, NULL);
        }
    }

    return 0;
}
