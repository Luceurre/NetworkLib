#include <iostream>
#include <thread>
#include "sockets.h"
#include "GameServerNetworkInterface.h"
#include "GameClientNetworkInterface.h"

#define PORT "27030"

void server();
void client();

mySocket serverSock;
mySocket clientSock;
sockaddr addr;
socklen_t addr_len;

class A {
public:
    void foo() {bar();};
    virtual void bar(){cout << "I'm A" << endl;};
};

class B : public A {
public:
    void bar() override {cout << "I'm B" << endl;};
};

int main() {
    GameServerNetworkInterface test;
    test.initialize_socket();
    test.run_recv();

    sleep(1);

    GameClientNetworkInterface clt;
    clt.initialize_socket();
    Protocol p = CONNECT;
    clt.send_packet(&p, sizeof p);
    // send(clientSock, &p, sizeof p, 0);

    sleep(1);
    test.callQueue();

    /*
    ServerNetworkInterface x(PORT);
    x.initialize_socket();
    x.run_recv();
    */

    return 0;
}

void server() {
    sockaddr_storage their_addr;
    socklen_t addr_len = sizeof their_addr;
    char buffer[256];

    int status = recvfrom(serverSock, &buffer, sizeof buffer, 0, (sockaddr * )&their_addr, &addr_len);
    if (status < 0) {
        cout << "server: recvfrom error" << endl;
        return;
    } else {
        cout << "received something... : " << buffer << endl;
        cout << "creating response socket..." << endl;

        sleep(1);
        mySocket respSock = create_udp_client_socket(their_addr, addr_len);
        char buffer_resp[256] = "Yay dude!";
        cout << "sending response..." << endl;
        // sendto(respSock, buffer_resp, sizeof buffer_resp, 0, (sockaddr *) &their_addr, addr_len);
        sendto(serverSock, buffer_resp, sizeof buffer_resp, 0, (sockaddr *) &their_addr, addr_len);
    }
}

void client() {
    char buffer[256] = "Oy, World!";
    sockaddr_storage their_addr;
    socklen_t addr_len = sizeof their_addr;

    int status = sendto(clientSock, buffer, sizeof buffer, 0, &addr, addr_len);
    if (status < 0) {
        cout << "client: cannot send_packet cstring..." << endl;
        cout << errno << endl;
    }
    cout << "waiting for server response..." << endl;
    recv(clientSock, buffer, sizeof buffer, 0);
    cout << "client received: " << buffer << endl;
}
