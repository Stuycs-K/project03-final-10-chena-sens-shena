#include "../include/utils.h"

void convertLower(char *string)
{
    for (int i = 0; string[i]; i++)
        string[i] = tolower(string[i]);
}

int rand_int()
{
    int file = open("/dev/random", O_RDONLY);
    int n;
    int random_int = read(file, &n, 4);
    if (random_int == -1)
        exit(1);
    if (n < 0)
        n *= -1;
    return n;
}

void init_ncurses()
{
    initscr();
    start_color();
    init_pair('R', COLOR_RED, COLOR_BLACK);
    init_pair('G', COLOR_GREEN, COLOR_BLACK);
    init_pair('B', COLOR_BLUE, COLOR_BLACK);
}

void end_ncurses()
{
    attron(COLOR_PAIR('B'));
    printw("Press any key to exit...");
    attroff(COLOR_PAIR('B'));

    getch();
    endwin();
}

void write_all(char *msg, int index, struct player *players)
{
    char buff[BUFFER_SIZE];

    // if (index != 0) // client
    // {
    //     sprintf(buff, YELLOW "%s" CLEAR, players[index].name, msg);
    //     write(players[index].id, ERASE, strlen(ERASE));
    // }

    // clients
    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id != 0)
            write(players[i].id, buff, sizeof(buff));

    // host
    printw("%s", buff);
}
