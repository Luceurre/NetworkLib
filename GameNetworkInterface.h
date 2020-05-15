//
// Created by pglandon on 5/15/20.
//

#ifndef NETWORKLIB_GAMENETWORKINTERFACE_H
#define NETWORKLIB_GAMENETWORKINTERFACE_H

#include "AbstractNetworkInterface.h"

#define PORT "27030"

enum Protocol {
    HEALTH_CHECK,
    CONNECT
};

#define BUFFER_SIZE sizeof(Protocol)



// Met en place les protocoles de dialogue pour notre jeu!
class GameNetworkInterface : public AbstractNetworkInterface {
public:
    explicit GameNetworkInterface();
    void initialize_socket() override;

protected:
    char* port;
    // Common interface for server/client.
    // Should be call by childen.
    void handle_msg(MyMessage msg) override;
};


#endif //NETWORKLIB_GAMENETWORKINTERFACE_H
