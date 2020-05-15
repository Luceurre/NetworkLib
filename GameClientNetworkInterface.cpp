//
// Created by pglandon on 5/15/20.
//

#include "GameClientNetworkInterface.h"

void GameClientNetworkInterface::initialize_socket() {
    GameNetworkInterface::initialize_socket();

    socket_fd = create_udp_client_socket(HOSTNAME, port);
    connected = true;
}

void GameClientNetworkInterface::handle_recv() {

}
