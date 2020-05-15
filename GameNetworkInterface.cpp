//
// Created by pglandon on 5/15/20.
//

#include "GameNetworkInterface.h"

GameNetworkInterface::GameNetworkInterface() : AbstractNetworkInterface() {
    this->port = PORT;
}

void GameNetworkInterface::initialize_socket() {
    setBufferSize(BUFFER_SIZE * sizeof(char));
    max_attempt = MAX_ATTEMPT;
    wait_til_retry = WAIT_TIME;
}

void GameNetworkInterface::handle_msg(MyMessage msg) {
    Protocol aProtocol = *(Protocol *)msg.protocol;

    logFile << "Processing msg..." << endl;

    if (aProtocol == CONNECT) {
        cout << "connect" << endl;
    } else {
        cout << "health" << endl;
    }
}
