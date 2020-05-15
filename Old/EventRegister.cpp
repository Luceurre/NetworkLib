//
// Created by pglandon on 5/4/20.
//

#include "EventRegister.h"

std::string EventRegister::descriptor() {
    return "(EventRegister)";
}

void EventRegister::register_event(const std::string& event_name) {
    Uint32 myEventType = SDL_RegisterEvents(1);
    registered_events.emplace(event_name, myEventType);

    info("Registering event : " + event_name);
}

void EventRegister::push_event(const std::string &event_name) {
    SDL_Event event;
    fill_event(event_name, &event);
    SDL_PushEvent(&event);
}

void EventRegister::fill_event(const std::string &event_name, SDL_Event* event) {
    SDL_zero(*event);
    auto p = registered_events.find(event_name);
    if (p == registered_events.end()) {
        warn("Event : " + event_name + " not found.");
        return;
    }
    event->type = p->second;
}

void EventRegister::print_events() {
    for(auto p : registered_events) {
        info(p.first);
    }
}
