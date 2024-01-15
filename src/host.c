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

    attron(COLOR_PAIR('G'));
    printw(">>> %s joined <<<\n", name);
    attroff(COLOR_PAIR('G'));
    refresh();

    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id == 0)
        {
            players[i].id = client_socket;
            players[i].points = 0;
            strcpy(players[i].name, name);
            break;
        }
}

void disconnect(int client_socket, int index, struct player *players)
{
    attron(COLOR_PAIR('R'));
    printw(">>> %s left <<<\n", players[index].name);
    attroff(COLOR_PAIR('R'));
    refresh();

    close(client_socket);
    players[index].id = 0;
}

void handle_client(fd_set read_fds, struct player *players, char *song_name)
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
                award_point(players, MAX_PLAYERS, client_socket, msg, song_name);
            }
            else
                disconnect(client_socket, i, players);
        }
    }
}

void server_listen(int listen_socket, fd_set read_fds, struct player *players, char *song_name)
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

    handle_client(read_fds, players, song_name);
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

    int song_pid = 0;

    struct timeval start_time, current_time;
    gettimeofday(&start_time, NULL);
    char *buff = malloc(sizeof(char) * BUFFER_SIZE);
    struct song cur_song;

    init_ncurses();

    attron(COLOR_PAIR('B'));
    printw("Waiting for players...\n");
    attroff(COLOR_PAIR('B'));
    refresh();

    while (total_played_songs <= total_songs)
    {
        server_listen(listen_socket, read_fds, players, cur_song.name); // blocks until something happens

        gettimeofday(&current_time, NULL);
        double elapsed_time = difftime(current_time.tv_sec, start_time.tv_sec);

        if (elapsed_time > ROUND_DURATION)
        {
            leaderboard(players, buff);
            write_all(buff, 0, players);

            if (total_played_songs == total_songs)
                break;

            cur_song = random_song(songs, total_songs, played_songs, total_played_songs);
            printf("Song Name (FOR TESTING): %s\n", cur_song.name);

            // kill PID
            if (song_pid != 0)
                err(kill(song_pid, SIGKILL), "kill error");

            song_pid = play_song(cur_song.file_name); // MOVE TO SERVER
            played_songs[total_played_songs] = cur_song;
            total_played_songs++;

            // reset start time
            gettimeofday(&start_time, NULL);
        }
    }

    err(kill(song_pid, SIGKILL), "kill error");
    end_ncurses();

    return 0;
}
