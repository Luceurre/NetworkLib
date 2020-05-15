//
// Created by pglandon on 5/4/20.
//

#ifndef ATELIERPROG_SOCKETS_HELPER_H
#define ATELIERPROG_SOCKETS_HELPER_H

#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <zconf.h>

#define cross_socket int
#define PORT "1234"
#define MAX_BUFFER_SIZE 1024

using namespace std;

struct SocketAddress
{
    struct sockaddr_storage addr;
    socklen_t addr_len;
};

// Handle if address is IPv4 or IPv6
void *get_in_addr(sockaddr *sa);
// Create UDP socket binded at a given port, with handy options (rebind port if already used for example)
// returns < 0 if socket creation fails
cross_socket get_server_udp_socket(char* port);
// Same with client, actually connect the socket -> don't need to use recvfrom/sendfrom
cross_socket get_client_udp_socket(char* hostname, char* port);
bool socket_cmp(struct SocketAddress *left, struct SocketAddress *right);

#endif //ATELIERPROG_SOCKETS_HELPER_H
