#include "../include/networking.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char *server_address)
{
    clear_stack();
    
    // getaddrinfo
    struct addrinfo *hints, *results;
    hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;

    getaddrinfo(server_address, PORT, hints, &results);

    // create the socket
    int serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    // connect to the server
    connect(serverd, results->ai_addr, results->ai_addrlen);

    free(hints);
    freeaddrinfo(results);

    return serverd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket)
{
    clear_stack();
    
    // accept the client connection
    struct sockaddr_storage client_address;
    socklen_t sock_size = sizeof(client_address);

    int client_socket = accept(listen_socket, (struct sockaddr *)&client_address, &sock_size);

    return client_socket;
}

/*Create and bind a socket.
 * Place the socket in a listening state.
 */
int server_setup()
{
    clear_stack();
    
    // setup structs for getaddrinfo
    struct addrinfo *hints, *results;
    hints = calloc(1, sizeof(struct addrinfo));

    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, hints, &results);

    // create socket
    int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    // this code allows the port to be freed after program exit.  (otherwise wait a few minutes)
    int yes = 1;
    err(setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)), "sockopt error");

    // bind the socket to address and port
    err(bind(clientd, results->ai_addr, results->ai_addrlen), "bind error");

    // set socket to listen state
    listen(clientd, 10);

    // free the structs used by getaddrinfo
    free(hints);
    freeaddrinfo(results);

    return clientd;
}

void err(int i, char *message)
{
    clear_stack();
    
    if (i < 0)
    {
        printf("Error: %s - %s\n", message, strerror(errno));
        exit(1);
    }
}
