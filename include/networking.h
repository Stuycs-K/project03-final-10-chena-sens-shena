#ifndef NETWORKING_H
#define NETWORKING_H

#include "imports.h"
#include "utils.h"

void err(int i, char *message);
int server_setup();
int client_tcp_handshake(char *server_address);
int server_tcp_handshake(int listen_socket);

#endif
