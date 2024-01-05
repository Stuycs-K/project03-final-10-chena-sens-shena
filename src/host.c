#include "../include/networking.h"

void rot13(char *str)
{
    int i;

    for (i = 0; str[i]; ++i)
        if (('A' <= str[i] && str[i] <= 'M') || ('a' <= str[i] && str[i] <= 'm'))
            str[i] += 13;
        else if (('N' <= str[i] && str[i] <= 'Z') || ('n' <= str[i] && str[i] <= 'z'))
            str[i] -= 13;

    str[i - 1] = '\0';
}

void subserver_logic(int client_socket)
{
    char buff[BUFFER_SIZE];

    while (1)
    {
        read(client_socket, buff, sizeof(buff));
        rot13(buff);
        write(client_socket, buff, sizeof(buff));
    }
}

int main(int argc, char *argv[])
{
    int listen_socket = server_setup();

    while (1)
    {
        int client_socket = server_tcp_handshake(listen_socket);

        if (fork() == 0)
        {
            subserver_logic(client_socket);
            exit(0);
        }

        close(client_socket);
    }

    return 0;
}
