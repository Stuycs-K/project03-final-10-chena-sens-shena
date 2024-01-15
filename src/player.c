#include "../include/networking.h"
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    char *IP = "127.0.0.1";

    if (argc > 1)
        IP = argv[1];

    int server_socket = client_tcp_handshake(IP);

    init_ncurses();
    char name[NAME_SIZE];

    attron(COLOR_PAIR('B'));
    printw("Successfully connected to %s\n", IP);
    printw("Enter your name: ");
    attroff(COLOR_PAIR('B'));
    scanw("%s", name);
    refresh();

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
            {
                printw("%s", buff);
                refresh();
            }
            else
            {
                attron(COLOR_PAIR('R'));
                printw(">>> Server disconnected <<<\n");
                attroff(COLOR_PAIR('R'));
                refresh();

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
