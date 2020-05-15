//
// Created by pglandon on 5/4/20.
//

#include "Client.h"

// TODO : add timeout
// TODO : add select or poll implementation

void Client::handle_recv() {
    SDL_Event event;
    int status;

    cout << "Hi, i'm client and i'm waiting further instructions!" << endl;

    while (listening) {
        cout << "Waiting reception..?" << endl;
        status = recv(client_socket, &event, sizeof event, 0);
        if (status < 0) {
            cout << "client: error recv" << endl;
            break;
        }

        SDL_Event event_askconnect;
        SDL_Event event_connect;
        er->fill_event(AskConnected, &event_askconnect);
        er->fill_event(Connected, &event_connect);

        cout << "Received something ?" << endl;

        if (event.type == event_askconnect.type) {
            cout << "Healthchecks works :)" << endl;
            send(client_socket, &event_connect, sizeof event_askconnect, 0);
        }
    }
}

void Client::send_cstring(char *buffer, int buffer_size) {
    int status = send(client_socket, buffer, buffer_size, 0);
    if (status == -1) {
        cout << "client: cannot send cstring" << endl;
    }
}

Client::Client() {
    client_socket = get_client_udp_socket("localhost", "2020");
    er = &EventRegister::getInstance();

    registerNetworkEvents();
    listening = true;

    recvThread = thread(&Client::handle_recv, this);
}

Client::~Client() {
    listening = false;
    close(client_socket);

    if (recvThread.joinable())
        recvThread.join();
}

void Client::connect() {
    SDL_Event eco;
    er->fill_event(Connected, &eco);

    int status = send(client_socket, &eco, sizeof eco, 0);
    if (status < 0) {
        cout << "client: failed send" << endl;
    } else {
        cout << "client: sending something..." << endl;
    }
}

std::string Client::descriptor() {
    return "(Client)";
}
