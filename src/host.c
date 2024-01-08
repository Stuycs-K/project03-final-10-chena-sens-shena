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

void handle_client(fd_set read_fds, int *clients)
{
    char buff[BUFFER_SIZE];

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        int client_socket = clients[i];

        if (FD_ISSET(client_socket, &read_fds))
        {
            if (read(client_socket, buff, sizeof(buff)))
            {
                for (int j = 0; j < MAX_CLIENTS; ++j)
                    if (i != j && clients[j] != 0)
                        write(clients[j], buff, sizeof(buff));
            }
            else
            {
                close(client_socket);
                clients[i] = 0;
            }
        }
    }
}

int main()
{
    int listen_socket = server_setup();

    fd_set read_fds;

    int clients[MAX_CLIENTS];

    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(listen_socket, &read_fds);

        int max_socket = listen_socket;

        for (int i = 0; i < MAX_CLIENTS; ++i)
        {
            int client_socket = clients[i];

            if (client_socket > 0)
                FD_SET(client_socket, &read_fds);

            if (client_socket > max_socket)
                max_socket = client_socket;
        }

        err(select(max_socket + 1, &read_fds, NULL, NULL, NULL), "select error");

        if (FD_ISSET(listen_socket, &read_fds))
            handle_new_client(listen_socket, clients);

        handle_client(read_fds, clients);
    }

    return 0;
}
