#include "../include/networking.h"

void clientLogic(int server_socket)
{
    char buff[BUFFER_SIZE];

    while (1)
    {
        fgets(buff, BUFFER_SIZE, stdin);
        write(server_socket, buff, sizeof(buff));

        read(server_socket, buff, sizeof(buff));
        printf("-> %s\n", buff);
    }
}

int main(int argc, char *argv[])
{
    char *IP = "127.0.0.1";

    if (argc > 1)
        IP = argv[1];

    int server_socket = client_tcp_handshake(IP);
    printf("client connected.\n");

    clientLogic(server_socket);

    return 0;
}
