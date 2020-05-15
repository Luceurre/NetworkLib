//
// Created by pglandon on 5/15/20.
//

#ifndef NETWORKLIB_GAMECLIENTNETWORKINTERFACE_H
#define NETWORKLIB_GAMECLIENTNETWORKINTERFACE_H


#include "GameNetworkInterface.h"

#define HOSTNAME "cxhome.org"

class GameClientNetworkInterface : public GameNetworkInterface {
protected:
    void handle_recv() override;
    bool isConnectedToServer = false;
    std::thread queue_thread;
public:
    GameClientNetworkInterface();
    ~GameClientNetworkInterface();

    void initialize_socket() override;
    void handle_msg(MyMessage msg) override;

    bool try_connect();

    void callQueue();
    void run_queue();
};


#endif //NETWORKLIB_GAMECLIENTNETWORKINTERFACE_H
