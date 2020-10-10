cmake_minimum_required(VERSION 3.15)
project(socket)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(include/)
AUX_SOURCE_DIRECTORY(src dir_srcs)

add_executable(socket src/main.cpp src/socket.cpp include/socket.hpp)
add_executable(socket-client src/socket_client.cpp src/socket.cpp include/socket.hpp)
add_executable(socket-server src/socket_server.cpp src/socket.cpp include/socket.hpp)