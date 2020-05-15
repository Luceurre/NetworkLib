//
// Created by pglandon on 5/4/20.
//

#ifndef ATELIERPROG_OLDCLIENT_H
#define ATELIERPROG_CLIENT_H

#include <thread>
#include "sockets_helper.h"
#include "server_events.h"
#include "EventRegister.h"

class Client : protected Logger {
cross_socket client_socket;
void handle_recv();
bool listening;
EventRegister* er;
thread recvThread;
std::string descriptor();

public:
    Client();
    ~Client();

    void send_cstring(char* buffer, int buffer_size);
    void connect();
};


#endif //ATELIERPROG_OLDCLIENT_H
