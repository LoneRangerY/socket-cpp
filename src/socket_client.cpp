//
// Created by yuancunkuan on 2020/10/10.
//
#include "socket.hpp"
#include <iostream>

int main() {
    try {
        socket_cpp::SocketUDP sock;
        sock.bind(3000);
        sock.send("127.0.0.1", 2000, "hello, world");
        socket_cpp::Datagram received = sock.receive();
        std::cout << received.data << std::endl;
        sock.close();
    } catch (socket_cpp::SocketException &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
