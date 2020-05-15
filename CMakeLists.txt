cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_FLAGS -pthread)
project(NetworkLib)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetworkLib main.cpp sockets.cpp sockets.h AbstractNetworkInterface.cpp AbstractNetworkInterface.h GameNetworkInterface.cpp GameNetworkInterface.h GameServerNetworkInterface.cpp GameServerNetworkInterface.h GameClientNetworkInterface.cpp GameClientNetworkInterface.h)