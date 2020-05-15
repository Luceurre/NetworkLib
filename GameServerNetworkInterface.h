//
// Created by pglandon on 5/15/20.
//

#ifndef NETWORKLIB_GAMESERVERNETWORKINTERFACE_H
#define NETWORKLIB_GAMESERVERNETWORKINTERFACE_H


#include <vector>
#include "GameNetworkInterface.h"

class GameServerNetworkInterface : public GameNetworkInterface{
public:
    void initialize_socket() override;
    void run_recv();
    ~GameServerNetworkInterface();

    void callQueue();

protected:
    void handle_recv() override;
    std::thread recvThread;

    std::vector<MyAddr> clientsAddr;
    void addClient(MyAddr addr);
    bool listening;
    void handle_msg(MyMessage msg) override;
};


#endif //NETWORKLIB_GAMESERVERNETWORKINTERFACE_H
