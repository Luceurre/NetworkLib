//
// Created by pglandon on 5/15/20.
//

#include "AbstractNetworkInterface.h"

AbstractNetworkInterface::AbstractNetworkInterface() {
    socket_fd = -1;
    connected = false;
    buffer_size = 0;
    buffer = nullptr;
    flags = 0;
    bufferSizeIsSet = false;
    listening = false;

    addr_len = sizeof their_addr;
}

void AbstractNetworkInterface::send_packet(void *buffer, std::size_t buffer_size) {
    if (!connected) {
        cout << "Socket isn't a connected one, you should specify the address!" << endl;
        return;
    }
    int status = send(socket_fd, buffer, buffer_size, 0);
    if (status < 0) {
        cout << "Can't send packet." << endl;
    }
}

void AbstractNetworkInterface::send_packet(void *buffer, std::size_t buffer_size, MyAddr addr) {
    int status = sendto(socket_fd, buffer, buffer_size, 0, (sockaddr *)&addr.addr, addr.addr_len);
    if (status < 0) {
        cout << "Can't send packet." << endl;
    }
}

void AbstractNetworkInterface::recv_packet() {
    listening = true;
    while (listening) {
        int status;
        void* local_buffer = malloc(buffer_size);

        if (connected) {
            status = recv(socket_fd, local_buffer, buffer_size, flags);
        } else {
            status = recvfrom(socket_fd, local_buffer, buffer_size, flags, (sockaddr *) &their_addr, &addr_len);
        }

        if (status < 0) {
            cout << "Couldn't receive packet" << endl;
            cout << errno << endl;
            return;
        }

        // On s'arrête ici si jamais la donnée dans buffer n'a pas fini d'être utilisé.
        std::unique_lock<std::mutex> lock(recv_mutex);

        MyMessage msg;
        msg.protocol = local_buffer;
        msg.sender.addr = their_addr;
        msg.sender.addr_len = addr_len;

        protocolQueue.emplace(msg);
        // TODO : free local_buffer memory when emptying queue!
        // TODO : move recv_thread to AbstractClass
        lock.unlock();
    }
}

void AbstractNetworkInterface::setBufferSize(size_t buffer_size) {
    if(bufferSizeIsSet) {
        cout << "You should set the buffer size only once!" << endl;
        return;
    }
    this->buffer_size = buffer_size;
    bufferSizeIsSet = true;
    buffer = malloc(buffer_size);
}

AbstractNetworkInterface::~AbstractNetworkInterface() {
    free(buffer);
}

void AbstractNetworkInterface::handle_protocol_queue() {
    // TODO : add some queue refresh rate
    while (!protocolQueue.empty()) {
        std::unique_lock<std::mutex> lock(recv_mutex);
        MyMessage p = protocolQueue.front();
        protocolQueue.pop();
        lock.unlock();

        handle_msg(p);
        free(p.protocol);
    }
}
