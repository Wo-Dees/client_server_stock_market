cmake_minimum_required(VERSION 3.2)

project(ClientStockMarket)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

find_package(Boost 1.40 COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(client main.cpp assistant.cpp client.cpp)
target_link_libraries(client PRIVATE Threads::Threads ${Boost_LIBRARIES})
