cmake_minimum_required(VERSION 3.14)
project(webServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)
