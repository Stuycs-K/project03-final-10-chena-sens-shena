#include "../include/utils.h"

void convertLower(char *str)
{
    clear_stack();
    
    for (; *str; str++) *str = tolower(*str);
}

int rand_int()
{
    clear_stack();

    int file = open("/dev/random", O_RDONLY);
    int n = -1;
    int random_int = read(file, &n, 4);
    if (random_int == -1)
        exit(1);
    if (n < 0)
        n *= -1;
    return n;
}

void write_all(char *msg, int index, struct player *players)
{
    clear_stack();

    char buff[BUFFER_SIZE] = {0};

    if (index != 0) // client
    {
        sprintf(buff, YELLOW "%s: " CLEAR "%s", players[index].name, msg);
        write(players[index].id, ERASE, strlen(ERASE));
    }
   

    for (int i = 0; i < MAX_PLAYERS; ++i)
        if (players[i].id != 0)
            write(players[i].id, buff, sizeof(buff));

    printf("%s", buff);
}

// The funny man in my dreams say this prevents funny characters 
void clear_stack() 
{
    volatile char buffer[0x10000] = {0};
    memset(buffer, 0x00, 0x10000);
    asm("");
}