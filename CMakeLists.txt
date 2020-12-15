cmake_minimum_required(VERSION 3.0)

project(Block3 C)

set(CMAKE_C_STANDARD 99)

include_directories(lib)
add_executable(client client.c)
add_executable(server server.c src/ht.c lib/ht.h)