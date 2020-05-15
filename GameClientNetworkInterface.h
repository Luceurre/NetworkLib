//
// Created by pglandon on 5/15/20.
//

#ifndef NETWORKLIB_GAMECLIENTNETWORKINTERFACE_H
#define NETWORKLIB_GAMECLIENTNETWORKINTERFACE_H


#include "GameNetworkInterface.h"

#define HOSTNAME "127.0.0.1"

class GameClientNetworkInterface : public GameNetworkInterface {
protected:
    void handle_recv() override;
public:
    void initialize_socket() override;
};


#endif //NETWORKLIB_GAMECLIENTNETWORKINTERFACE_H
