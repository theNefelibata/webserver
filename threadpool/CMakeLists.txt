cmake_minimum_required(VERSION 3.14)
project(threadpool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(./src SRC_LIST)
add_executable(test TestThreadPool.cpp ${SRC_LIST})

find_package(Threads REQUIRED)
target_link_libraries(test PUBLIC Threads::Threads)
