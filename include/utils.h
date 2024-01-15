#ifndef UTILS_H
#define UTILS_H

#include "imports.h"

void convertLower(char *string);
void init_ncurses();
int rand_int();
void write_all(char *msg, int index, struct player *players);

#endif
