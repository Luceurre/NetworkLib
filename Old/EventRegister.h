//
// Created by pglandon on 5/4/20.
//

#ifndef ATELIERPROG_EVENTREGISTER_H
#define ATELIERPROG_EVENTREGISTER_H

#include <map>

#include "../API/Logger.h"

// Singleton class to register user events across the program.
// TODO : make it thread-safe (même si en vrai ça devrait être bon étant donné qu'on devrait pas enregistrer des events en cours de route).
class EventRegister : protected Logger {

protected:
    // On associe une chaine de caractère à un événement ?
    // why not...
    std::map<std::string, Uint32> registered_events;

    std::string descriptor() override;
public:
    static EventRegister& getInstance()
    {
        static EventRegister instance;
        return instance;
    }
    EventRegister(EventRegister const&) = delete;
    void operator=(EventRegister const&) = delete;

    EventRegister() = default;
    void register_event(const std::string& event_name);
    void push_event(const std::string& event_name);
    void fill_event(const std::string& event_name, SDL_Event* event);
    void print_events();
};

#endif //ATELIERPROG_EVENTREGISTER_H
