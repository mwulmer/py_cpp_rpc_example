cmake_minimum_required(VERSION 3.10.2)
project(network_communication_examples-rpc)

include_directories(include)

add_executable(rpc_server src/rpc_server.cpp)
target_link_libraries(rpc_server pthread)

add_executable(rpc_client src/rpc_client.cpp)
target_link_libraries(rpc_client pthread)
