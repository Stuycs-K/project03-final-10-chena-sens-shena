#include "../include/networking.h"
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    char *IP = "127.0.0.1";

    if (argc > 1)
        IP = argv[1];

    int server_socket = client_tcp_handshake(IP);
    printf("Successfully connected to %s\n", IP);

    char name[NAME_SIZE];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    write(server_socket, name, sizeof(name));

    char buff[BUFFER_SIZE];
    fd_set read_fds;

    while (1)
    {
        FD_ZERO(&read_fds);

        FD_SET(server_socket, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        err(select(server_socket + 1, &read_fds, NULL, NULL, NULL), "select error");

        if (FD_ISSET(server_socket, &read_fds))
        {
            if (read(server_socket, buff, sizeof(buff)))
                printf("%s", buff);
            else
            {
                printf(RED BOLD ">>> Server disconnected <<<\n" CLEAR);
                close(server_socket);
                break;
            }
        }
        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            fgets(buff, sizeof(buff), stdin);
            write(server_socket, buff, sizeof(buff));
        }
    }

    return 0;
}
