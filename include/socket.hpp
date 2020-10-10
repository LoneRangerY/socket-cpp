//
// Created by yuancunkuan on 2020/10/9.
//

#ifndef SOCKET_CPP_SOCKET_HPP
#define SOCKET_CPP_SOCKET_HPP

#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <stdlib.h>

#include <arpa/inet.h>

#define MAX_BUFFER 1024

namespace socket_cpp {

    typedef std::string IP;
    typedef unsigned int Port;
    typedef std::string Data;

    struct Address {
        IP ip;
        Port port;
    };

    struct Datagram {
        Address address;
        Data data;
    };

    class SocketException {
    public:
        SocketException(const std::string &error) { this->message_ = error; }
        virtual const char* what() {return this->message_.c_str(); }
    private:
        std::string message_;
    };

    class SocketUDP {
    public:
        SocketUDP();
        virtual ~SocketUDP();
        void close();
        void bind(Port port);
        void send(IP ip, Port port, Data data);
        Datagram receive();
    private:
        int socket_id_;
        bool binded_;
    };

} // namespace socket_cpp

#endif //SOCKET_CPP_SOCKET_HPP
