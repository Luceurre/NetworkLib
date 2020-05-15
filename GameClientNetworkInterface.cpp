//
// Created by pglandon on 5/15/20.
//

#include "GameClientNetworkInterface.h"

void GameClientNetworkInterface::initialize_socket() {
    GameNetworkInterface::initialize_socket();

    socket_fd = create_udp_client_socket(HOSTNAME, port);
    connected = true;

    logFile.open("log_client.txt");
}

void GameClientNetworkInterface::handle_recv() {

}

GameClientNetworkInterface::GameClientNetworkInterface() : GameNetworkInterface() {
    isConnectedToServer = false;
}

void GameClientNetworkInterface::handle_msg(MyMessage msg) {
    GameNetworkInterface::handle_msg(msg);
    Protocol aProtocol = *(Protocol *)msg.protocol;

    if (aProtocol == CONNECT) {
        isConnectedToServer = true;
    }
}

void GameClientNetworkInterface::callQueue() {
    handle_protocol_queue();
}

bool GameClientNetworkInterface::try_connect() {
    int attempt = 0;
    while (!isConnectedToServer && attempt < max_attempt) {
        cout << "trying to connect, attempt n°" << attempt << endl;
        Protocol p = CONNECT;
        send_packet(&p, sizeof p);
        attempt++;
        sleep(wait_til_retry);
    }

    return isConnectedToServer;
}

void GameClientNetworkInterface::run_queue() {
    queue_thread = std::thread(&GameClientNetworkInterface::handle_protocol_queue, this);
}

GameClientNetworkInterface::~GameClientNetworkInterface() {
    logFile.close();
    if (queue_thread.joinable())
        queue_thread.join();
}
