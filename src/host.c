#include "../include/networking.h"

void handle_new_client(int listen_socket, int *clients)
{
    int client_socket = server_tcp_handshake(listen_socket);
    err(client_socket, "client accept error");

    printf("Client %d joined\n", client_socket);

    for (int i = 0; i < MAX_CLIENTS; ++i)
        if (clients[i] == 0)
        {
            clients[i] = client_socket;
            break;
        }
}

int main()
{
    int listen_socket = server_setup();

    fd_set read_fds;

    int clients[MAX_CLIENTS];
    char buff[BUFFER_SIZE];

    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(listen_socket, &read_fds);

        err(select(listen_socket + 1, &read_fds, NULL, NULL, NULL), "select error");

        if (FD_ISSET(listen_socket, &read_fds))
            handle_new_client(listen_socket, clients);
    }

    return 0;
}
