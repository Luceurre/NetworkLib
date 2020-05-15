//
// Created by pglandon on 5/15/20.
//

#ifndef NETWORKLIB_ABSTRACTNETWORKINTERFACE_H
#define NETWORKLIB_ABSTRACTNETWORKINTERFACE_H


#include <mutex>
#include <thread>
#include <queue>
#include "sockets.h"

class AbstractNetworkInterface {
private:
    bool bufferSizeIsSet;
    std::size_t buffer_size;
public:
    AbstractNetworkInterface();
    ~AbstractNetworkInterface();

    virtual void initialize_socket() = 0;

    // Attention, méthode bloquante! Rempli buffer, buffer_size et their_addr
    // avec les informations du dernier paquet recu puis appel handle_recv.
    void recv_packet();

    void send_packet(void* buffer, std::size_t buffer_size);

protected:
    void setBufferSize(size_t buffer_size);
    mySocket socket_fd;
    bool connected;
    bool listening;

    std::queue<MyMessage> protocolQueue;

    void* buffer;
    std::mutex recv_mutex;
    sockaddr_storage their_addr;
    socklen_t addr_len;
    int flags;

    void send_packet(void* buffer, std::size_t buffer_size, MyAddr addr);

    // Gère le contenu de buffer
    // deprectated
    virtual void handle_recv() = 0;
    virtual void handle_msg(MyMessage msg) = 0;
    void handle_protocol_queue();
};


#endif //NETWORKLIB_ABSTRACTNETWORKINTERFACE_H
