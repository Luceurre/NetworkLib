//
// Created by pglandon on 5/4/20.
//

#include "server_events.h"
#include "EventRegister.h"

// On utilise une variable globale ici, parce que.
bool registered = false;

void registerNetworkEvents() {
    if (registered)
        return;

    std::cout << "Registering network events..." << std::endl;

    EventRegister* er = &EventRegister::getInstance();

    er->register_event(AskConnected);
    er->register_event(Connected);
    er->register_event(Disconnect);

    registered = true;
}