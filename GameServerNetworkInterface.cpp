//
// Created by pglandon on 5/15/20.
//

#include "GameServerNetworkInterface.h"

void GameServerNetworkInterface::initialize_socket() {
    GameNetworkInterface::initialize_socket();
    socket_fd = create_udp_server_socket(port);
    logFile.open("server_log.txt");
}

void GameServerNetworkInterface::handle_recv() {
    Protocol p = *(Protocol *)buffer;

    if (p == HEALTH_CHECK)
        cout << "I'm alive baaaaby" << endl;

    cout << "received!" << endl;
    cout << (char *) buffer << endl;
}


GameServerNetworkInterface::~GameServerNetworkInterface() {
    logFile.close();
    if (queue_thread.joinable())
        queue_thread.join();
}

void GameServerNetworkInterface::callQueue() {
    handle_protocol_queue();
}

void GameServerNetworkInterface::handle_msg(MyMessage msg) {
    GameNetworkInterface::handle_msg(msg);
    Protocol aProtocol = *(Protocol *)msg.protocol;

    if (aProtocol == CONNECT) {
        // Une nouvelle connection ?
        add_client(msg.sender);
        // On prévient le client qu'il a été ajouté
        Protocol answer = CONNECT;
        send_packet(&answer, msg.sender);
    }
}

void GameServerNetworkInterface::add_client(MyAddr clientAddr) {
    // TODO : check for duplicate
    cout << "added client!" << endl;
    clientsAddr.push_back(clientAddr);
}

void GameServerNetworkInterface::run_queue() {
    queue_thread = std::thread(&GameServerNetworkInterface::handle_protocol_queue, this);
}

