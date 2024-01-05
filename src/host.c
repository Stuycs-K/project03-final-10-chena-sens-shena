#include "../include/networking.h"

void subserver_logic(int client_socket)
{
    char buff[BUFFER_SIZE];

    while (1)
    {
        
        // read(client_socket, buff, sizeof(buff));
        // write(client_socket, buff, sizeof(buff));
    }
}

int main(int argc, char *argv[])
{
    int listen_socket = server_setup();

    while (1)
    {
        int client_socket = server_tcp_handshake(listen_socket);
        printf("Client joined\n");

        if (fork() == 0)
        {
            subserver_logic(client_socket);
            exit(0);
        }

        close(client_socket);
    }
}
