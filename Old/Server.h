//
// Created by pglandon on 5/4/20.
//

#ifndef ATELIERPROG_SERVER_H
#define ATELIERPROG_SERVER_H

#include <arpa/inet.h>
#include <thread>
#include "sockets_helper.h"
#include "server_events.h"
#include "EventRegister.h"

#define MAX_CONNECTION 10

// Plutôt explicite comme nom, non ? :)
// Il discute qu'en SDL_Event, en espérant qu'on ait pas de problèmes entre
// les différentes archi (big endian, little endian, spacing,...)
class Server : protected Logger {
    // Associe une addresse à un timeout
    // On regarde depuis combien de temps on a pas reçu de messages de l'adresse?
    SocketAddress* connected;
    int* timeout;
    int currently_connected;

    cross_socket server_socket;
    void handle_recv();
    // Vérifie que les appareils répondent toujours à l'appel
    void healthcheck();

    thread recvThread;
    thread healthThread;

    EventRegister* er;

    bool running;

    std::string descriptor();
public:
    Server();
    ~Server();

    void wait();
};


#endif //ATELIERPROG_SERVER_H
