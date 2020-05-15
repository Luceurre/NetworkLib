//
// Created by pglandon on 5/15/20.
//

#include "GameServerNetworkInterface.h"

void GameServerNetworkInterface::initialize_socket() {
    GameNetworkInterface::initialize_socket();
    socket_fd = create_udp_server_socket(port);
}

void GameServerNetworkInterface::handle_recv() {
    Protocol p = *(Protocol *)buffer;

    if (p == HEALTH_CHECK)
        cout << "I'm alive baaaaby" << endl;

    cout << "received!" << endl;
    cout << (char *) buffer << endl;
}

void GameServerNetworkInterface::run_recv() {
    listening = true;
    recvThread = std::thread(&GameServerNetworkInterface::recv_packet, this);
}

GameServerNetworkInterface::~GameServerNetworkInterface() {
    if (recvThread.joinable())
        recvThread.join();
}

void GameServerNetworkInterface::addClient(MyAddr addr) {

}

void GameServerNetworkInterface::callQueue() {
    handle_protocol_queue();
}

void GameServerNetworkInterface::handle_msg(MyMessage msg) {
    GameNetworkInterface::handle_msg(msg);

    cout << "I'm server" << endl;
}
