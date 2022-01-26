cmake_minimum_required(VERSION 3.14)
project(webServer)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(./src SRC_LIST)

add_executable(server src/server.cpp src/utils.cpp src/Epoll.cpp src/InetAdress.cpp src/Socket.cpp src/Channel.cpp)
add_executable(client src/client.cpp src/utils.cpp src/Epoll.cpp src/InetAdress.cpp src/Socket.cpp src/Channel.cpp)
