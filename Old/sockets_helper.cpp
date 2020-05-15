//
// Created by pglandon on 5/4/20.
//

#include <sys/param.h>
#include "sockets_helper.h"

// Handle if address is IPv4 or IPv6
void *get_in_addr(sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((sockaddr_in*)sa)->sin_addr);
    }

    return &(((sockaddr_in6*)sa)->sin6_addr);
}

// Create UDP socket binded at a given port, with handy options (rebind port if already used for example)
// returns < 0 if socket creation fails
cross_socket get_server_udp_socket(char* port) {
    // our socket
    cross_socket socket_fd;
    // some address storage
    addrinfo hints, *serverInfo, *p;
    // to check the status of the function
    int status;
    // No boolean in C... opt = true
    int opt = 1;

    // Set hints to 0, avoid random results
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // don't care if it's IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // We want an UDP socket
    hints.ai_flags = AI_PASSIVE; // Autofill our IP address

    status = getaddrinfo(nullptr, port, &hints, &serverInfo);
    if (status != 0) {
        cout << "getaddrinfo: " << gai_strerror(status) << endl;
        return -1;
    }

    // loop through all the results and bind to the first we can
    for(p = serverInfo; p != nullptr; p = p->ai_next) {
        // Try to create the socket
        if ((socket_fd = socket(p->ai_family, p->ai_socktype,
                                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        // Try to set correct options
        if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            return -1;
        }

        // Try to bind it
        if (bind(socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
            // TODO : make close cross platform
            close(socket_fd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(serverInfo);
    if (p == nullptr) {
        cout << "server: failed to bind" << endl;
        return -1;
    }

    return socket_fd;
}

cross_socket get_client_udp_socket(char* hostname, char* port) {
    int socket_fd, status;
    addrinfo hints, *serverInfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    status = getaddrinfo(hostname, port, &hints, &serverInfo);
    if (status != 0) {
        cout << "getaddrinfo: " << gai_strerror(status) << endl;
        return -1;
    }

    // loop through all the results and make a socket
    for(p = serverInfo; p != nullptr; p = p->ai_next) {
        if ((socket_fd = socket(p->ai_family, p->ai_socktype,
                                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (p == nullptr) {
        cout << "client: failed to create socket" << endl;
        return -1;
    }

    status = connect(socket_fd, p->ai_addr, p->ai_addrlen);
    if (status == -1) {
        cout << "client: failed to connect socket" << endl;
        return -1;
    }

    freeaddrinfo(serverInfo);
    return socket_fd;
}

bool socket_cmp(struct SocketAddress *left, struct SocketAddress *right)
{
    socklen_t min_addr_len = MIN(left->addr_len, right->addr_len);

    int rv = memcmp(left, right, min_addr_len);
    return (rv == 0);
}