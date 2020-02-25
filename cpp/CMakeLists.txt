cmake_minimum_required(VERSION 3.10.2)
project(network_communication_examples
    LANGUAGES CXX
    )

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LINK_DEPENDS_NO_SHARED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wreturn-type")

add_subdirectory(rpc)
