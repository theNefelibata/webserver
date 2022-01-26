cmake_minimum_required(VERSION 3.14)
project(webServer)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(./src SRC_LIST)

add_executable(server server.cpp ${SRC_LIST})
add_executable(client client.cpp ${SRC_LIST})
