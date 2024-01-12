#include "../include/networking.h"
#include "../include/utils.h"
#include <sys/select.h>

void write_all(char *msg, int index, struct player *players)
{
    char buff[BUFFER_SIZE];
    sprintf(buff, YELLOW "%s: " CLEAR "%s", players[index].name, msg);

    write(players[index].id, ERASE, strlen(ERASE));

    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id != 0)
            write(players[i].id, buff, sizeof(buff));

    printf("%s", buff);
}

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

void handle_client(fd_set read_fds, struct player *players)
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
                // awardPoints()
            }
            else
                disconnect(client_socket, i, players);
        }
    }
}
int sizeofArray(struct player *players)
{
    int n = 0;
    int i = 0;
    while (players[i].id != 0)
        n++;
    return n;
}

int main()
{
    int listen_socket = server_setup();
    fd_set read_fds;
    struct player players[MAX_PLAYERS];

    // initialize_game(players);

    while (1)
    {
        // server_listen() {
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

        err(select(max_socket + 1, &read_fds, NULL, NULL, NULL), "select error"); // blocks, change last NULL
        // }

        // check the time, wait! either timeout or select unblocks
        //if someone gets right asnwer dont send that, just send that they got the right answer + were awarded poitns 

        // check stateful events

        if (FD_ISSET(listen_socket, &read_fds))
            handle_new_client(listen_socket, players);

        handle_client(read_fds, players);
    }

    return 0;
}
