#include "../include/networking.h"
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    char *IP = "127.0.0.1";

    if (argc > 1)
        IP = argv[1];

    int server_socket = client_tcp_handshake(IP);

    init_ncurses();
    char name[NAME_SIZE] = {0};

    printc("Successfully connected to ", 'B', 0);
    printc(IP, 'B', 1);
    printc("Enter your name: ", 'B', 0);
    scanw("%s", name);

    write(server_socket, name, sizeof(name));

    char buff[BUFFER_SIZE] = {0};
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
                printc(buff, 0, 0);
            else
            {
                printc(">>> Server disconnected <<<", 'R', 1);
                close(server_socket);
                end_ncurses();

                break;
            }
        }
        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            scanw("%s", buff);
            write(server_socket, buff, sizeof(buff));
        }
    }

    return 0;
}
