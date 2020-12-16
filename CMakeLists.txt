cmake_minimum_required(VERSION 3.15)

project(Block3 C)

set(CMAKE_C_STANDARD 99)

include_directories(lib)
add_executable(client client.c src/client_functions.c lib/client_functions.h)
add_executable(server server.c src/server_functions.c lib/server_functions.h)