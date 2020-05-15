//
// Created by pglandon on 5/4/20.
//

#include "Server.h"


Server::Server() {
    server_socket = get_server_udp_socket(PORT);

    running = true;

    timeout = new int[MAX_CONNECTION];
    connected = new SocketAddress[MAX_CONNECTION];
    currently_connected = 0;

    registerNetworkEvents();
    er = &EventRegister::getInstance();

    // On lance l'écoute...
    recvThread = thread(&Server::handle_recv, this);
    healthThread = thread(&Server::healthcheck, this);
}

void Server::handle_recv() {
    while (server_socket) {
        sockaddr_storage their_addr;
        socklen_t addr_len = sizeof their_addr;
        SDL_Event event;
        char s[INET6_ADDRSTRLEN];
        int status;

        cout << "server: waiting to recvfrom" << endl;

        status = recvfrom(server_socket, &event, sizeof event, 0, \
        (sockaddr *) &their_addr, &addr_len);
        if (status < 0) {
            cout << "server: recvfrom error" << endl;
            return;
        } else {
            cout << "received something..." << endl;
        }

        // Check if already connected
        SocketAddress newConnection{their_addr, addr_len};
        int index_found = -1;
        for(int i = 0; i < currently_connected; ++i) {
            if (socket_cmp(&newConnection, &connected[i])) {
                index_found = i;
                break;
            }
        }

        if (index_found < 0) {
            cout << "server: new connection!" << endl;
            connected[currently_connected] = newConnection;
            index_found = currently_connected;
            currently_connected++;
        }

        SDL_Event event_connected;
        er->fill_event(Connected, &event_connected);
        // On gére en fonction du paquet reçu
        if (event.type == event_connected.type) {
            timeout[index_found] = 0;
            cout << "La liaison est toujours active!" << endl;
        }
    }
}

void Server::wait() {
    recvThread.join();
}

Server::~Server() {
    running = false;

    close(server_socket);
    if (recvThread.joinable())je suis parti me chercher une biere je re

        recvThread.join();
    if (healthThread.joinable())
        healthThread.join();

}

void Server::healthcheck() {
    while (running) {
        cout << "checking health..." << endl;

        SDL_Event event;
        EventRegister::getInstance().fill_event(AskConnected, &event);

        for (int i = 0; i < currently_connected; ++i) {

            sendto(server_socket, &event, sizeof event, 0, (sockaddr *) &connected[i].addr, connected[i].addr_len);
            timeout[i]++;
            if (timeout[i] > 20) {
                // Remove connection
                cout << "Removing connection." << endl;
            }
        }

        SDL_Delay(1000);
        cout << "Asking if still there ? " << endl;
    }
}

std::string Server::descriptor() {
    return "(Server)";
}
