#ifndef UTILS_H
#define UTILS_H

#include "imports.h"

void init_ncurses();
void end_ncurses();
void printc(char *str, char color, int newline);
int rand_int();
void write_all(char *msg, int index, struct player *players);

#endif
