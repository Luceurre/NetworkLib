//
// Created by pglandon on 5/14/20.
//

// Une mini lib qui gère la création de sockets
// pour le client et le serveur, gère les erreurs, etc...

#ifndef NETWORKLIB_SOCKETS_H
#define NETWORKLIB_SOCKETS_H

#include <netdb.h>
#include <cstring>
#include <zconf.h>
#include <cstdio>

#include <iostream>

#define mySocket int

struct MyAddr {
    sockaddr_storage addr;
    socklen_t addr_len;
};

struct MyMessage {
    void* protocol;
    MyAddr sender;
};

using namespace std;
mySocket create_udp_server_socket(char* port);
mySocket create_udp_client_socket(char* hostname, char* port);
mySocket create_udp_client_socket(sockaddr_storage& addr, socklen_t& addr_len);
mySocket create_udp_client_socket(char* hostname, char* port, sockaddr& addr, socklen_t& addr_len);

#endif //NETWORKLIB_SOCKETS_H
