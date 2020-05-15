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

    //server();
    client();



    /*
    Protocol p = CONNECT;
    clt.send_packet(&p, sizeof p);
    // send(clientSock, &p, sizeof p, 0);

    sleep(1);
    test.callQueue();

    sleep(1);
    clt.callQueue();

    bool t = clt.try_connect();
    if(t) {
        cout << "connected!" << endl;
    } else {
        cout << "failure" << endl;
    }

     */
    /*
    ServerNetworkInterface x(PORT);
    x.initialize_socket();
    x.run_recv();
    */


    return 0;
}

void server() {
    GameServerNetworkInterface test;
    test.initialize_socket();
    test.run_recv();

    cout << "pute" << endl;
    test.run_queue();
}

void client() {
    GameClientNetworkInterface clt;
    clt.initialize_socket();
    clt.run_recv();
    clt.run_queue();

    sleep(1);

    if(clt.try_connect()) {
        cout << "connected!" << endl;
    } else {
        cout << "failure.." << endl;
    }
}