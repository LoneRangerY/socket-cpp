//
// Created by yuancunkuan on 2020/10/9.
//

#include "socket.hpp"

namespace socket_cpp {
    sockaddr_in* to_sockaddr(Address *a) {
        sockaddr_in *ret;
        ret = (sockaddr_in*)malloc(sizeof(sockaddr_in));
        ret->sin_family = AF_INET; // 地址族
        inet_aton(a->ip.c_str(), &(ret->sin_addr));
        ret->sin_port = htons(a->port);

        return ret;
    }
    Address* from_sockaddr(sockaddr_in *address) {
        Address *ret;
        ret = (Address*)malloc(sizeof(Address));
        ret->ip = inet_ntoa(address->sin_addr);
        ret->port = ntohs(address->sin_port);

        return ret;
    }

    SocketUDP::SocketUDP() {
        this->socket_id_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (this->socket_id_ == -1) throw SocketException("[Constructor] Cannot create socket");
        this->binded_ = false;
    }
    SocketUDP::~SocketUDP() {}
    void SocketUDP::close() {
        shutdown(this->socket_id_, SHUT_RDWR);
    }
    void SocketUDP::bind(Port port) {
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(port);

        if (this->binded_) {
            this->close();
            this->socket_id_ = socket(AF_INET, SOCK_DGRAM, 0);
            if (this->socket_id_ == -1) throw SocketException("[Bind] Cannot create socket");
        }

        if (::bind(this->socket_id_, (sockaddr*)&address, sizeof(sockaddr_in)) == -1) {
            std::stringstream error;
            error <<  "[listen_on_port] with [port=" << port << "] Cannot bind socket";
            throw SocketException(error.str());
        }

        this->binded_ = true;
    }
    void SocketUDP::send(IP ip, Port port, Data data) {
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        inet_aton(ip.c_str(), &address.sin_addr);

        if (sendto(this->socket_id_, (void*)data.c_str(), data.length() + 1, 0, (sockaddr*)&address, sizeof(sockaddr_in)) == -1) {
            std::stringstream error;
            error << "[send] with [ip=" << ip << "] [port=" << port << "] [data=" << data << "] Cannot send";
            throw SocketException(error.str());
        }
    }

    Datagram SocketUDP::receive() {
        int size = sizeof(sockaddr_in);
        char *buffer = (char*)malloc(sizeof(char) * MAX_BUFFER);
        sockaddr_in address;
        Datagram ret;
        if (recvfrom(this->socket_id_, (void*)buffer, MAX_BUFFER, 0, (sockaddr*)&address, (socklen_t*)&size) == -1)
            throw SocketException("[receive] Cannot receive");
        ret.data = buffer;
        ret.address.ip = inet_ntoa(address.sin_addr);
        ret.address.port = ntohs(address.sin_port);

        free(buffer);

        return ret;
    }

} // namespace socket_cpp
