#include "../include/utils.h"

int rand_int()
{
    int file = open("/dev/random", O_RDONLY);
    int n = -1;
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
    init_pair('Y', COLOR_YELLOW, COLOR_BLACK);
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

void printc(char *str, char color, int newline)
{
    attron(COLOR_PAIR(color));
    printw("%s", str);
    attroff(COLOR_PAIR(color));

    if (newline)
    {
        printw("\n");
        int x, y;
        getyx(stdscr, y, x);
        move(y, 0);
    }

    refresh();
}

void write_all(char *msg, int index, struct player *players)
{
    char buff[BUFFER_SIZE] = {0};

    if (index == 0) // host
        sprintf(buff, "%s: %s", "Host", msg);
    else // client
        sprintf(buff, "%s: %s", players[index].name, msg);

    // clients
    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id != 0)
            write(players[i].id, buff, sizeof(buff));

    // host
    clear();
    printc(buff, 'Y', 1);
}
