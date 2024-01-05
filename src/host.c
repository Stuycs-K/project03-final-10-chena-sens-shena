#include "../include/networking.h"

void subserver_logic(int listen_socket)
{
    fd_set read_fds;
    char buff[BUFFER_SIZE];

    while (1)
    {
        FD_ZERO(&read_fds);

        FD_SET(STDIN_FILENO, &read_fds);  // stdin
        FD_SET(listen_socket, &read_fds); // socket

        err(select(listen_socket + 1, &read_fds, NULL, NULL, NULL), "select error");

        if (FD_ISSET(STDIN_FILENO, &read_fds)) // stdin
        {
            fgets(buff, sizeof(buff), stdin);
            printf("[STDIN] %s\n", buff);
        }
        if (FD_ISSET(listen_socket, &read_fds)) // socket
        {
            int client_socket = server_tcp_handshake(listen_socket);
            printf("[SOCKET] Connected\n");

            read(client_socket, buff, sizeof(buff));
            printf("[SOCKET] %s\n", buff);

            // close(client_socket);
        }

        // read(client_socket, buff, sizeof(buff));
        // write(client_socket, buff, sizeof(buff));
    }
}

int main(int argc, char *argv[])
{
    int listen_socket = server_setup();
    subserver_logic(listen_socket);

    // while (1)
    // {
    //     int client_socket = server_tcp_handshake(listen_socket);
    //     printf("Client joined\n");

    //     if (fork() == 0)
    //     {
    //         subserver_logic(listen_socket, client_socket);
    //         exit(0);
    //     }

    //     close(client_socket);
    // }
}
