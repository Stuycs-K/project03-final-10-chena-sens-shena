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

void write_all(char *msg, int index, struct player *players)
{
    char buff[BUFFER_SIZE];

    if (index != 0) // client
    {
        sprintf(buff, YELLOW "%s: " CLEAR "%s", players[index].name, msg);
        write(players[index].id, ERASE, strlen(ERASE));
    }
    else // host
        sprintf(buff, YELLOW "%s: " CLEAR "%s", "Host", msg);

    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id != 0)
            write(players[i].id, buff, sizeof(buff));

    printf("%s", buff);
}
