cmake_minimum_required(VERSION 3.14)
project(P2P_Over_MiddleBoxes_Demo C)

set(CMAKE_C_STANDARD 11)

include_directories(p2pchat)
include_directories(tools)

add_executable(P2P_Over_MiddleBoxes_Demo
        p2pchat/tests/test_endpoint.c
        p2pchat/tests/test_eplist.c
        p2pchat/tests/test_logging.c
        p2pchat/tests/test_message.c
        p2pchat/client.c
        p2pchat/endpoint.c
        p2pchat/endpoint.h
        p2pchat/endpoint_list.c
        p2pchat/endpoint_list.h
        p2pchat/logging.c
        p2pchat/logging.h
        p2pchat/message.c
        p2pchat/message.h
        p2pchat/server.c
        tools/udp_client.c
        tools/udp_server.c)
