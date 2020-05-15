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
    ~GameServerNetworkInterface();

    void callQueue();
    void run_queue();
protected:
    std::thread queue_thread;
    void handle_recv() override;

    std::vector<MyAddr> clientsAddr;
    bool listening;
    void handle_msg(MyMessage msg) override;

    // Server side method
    // Ajoute un client à la liste des clients enregistrés
    void add_client(MyAddr clientAddr);
};


#endif //NETWORKLIB_GAMESERVERNETWORKINTERFACE_H
