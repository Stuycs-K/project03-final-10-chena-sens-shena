#include "../include/networking.h"
#include "../include/utils.h"

void write_all(char *msg, int i, struct player *players)
{
    char buff[BUFFER_SIZE];
    sprintf(buff, "%s: %s", players[i].name, msg);

    for (int j = 0; j < MAX_PLAYERS; ++j)
        if (i != j && players[j].id != 0)
            write(players[j].id, buff, sizeof(buff));
}

void handle_new_client(int listen_socket, struct player *players)
{
    char name[NAME_SIZE];

    int client_socket = server_tcp_handshake(listen_socket);
    err(client_socket, "client accept error");

    read(client_socket, name, sizeof(name));
    printf("%s (%d) joined\n", name, client_socket);

    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id == 0)
        {
            players[i].id = client_socket;
            strcpy(players[i].name, name);
            break;
        }
}

void handle_client(fd_set read_fds, struct player *players)
{
    char msg[BUFFER_SIZE - NAME_SIZE];

    for (int i = 0; i < MAX_PLAYERS; ++i)
    {
        int client_socket = players[i].id;

        if (FD_ISSET(client_socket, &read_fds))
        {
            if (read(client_socket, msg, sizeof(msg)))
                write_all(msg, i, players);
            else
            {
                close(client_socket);
                players[i].id = 0;
            }
        }
    }
}

int main()
{
    int listen_socket = server_setup();

    fd_set read_fds;

    struct player players[MAX_PLAYERS];

    while (1)
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

    return 0;
}
