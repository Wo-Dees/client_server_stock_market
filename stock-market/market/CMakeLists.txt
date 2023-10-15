cmake_minimum_required(VERSION 3.22)

project(MarketSimulator)

FIND_PACKAGE(Boost 1.40 COMPONENTS system REQUIRED)
FIND_PACKAGE(Catch2 REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS -Wall -Werror}")

include_directories(${Boost_INCLUDE_DIR})
include_directories(${Catch2_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(play main.cpp)
TARGET_LINK_LIBRARIES(play PRIVATE Threads::Threads ${Boost_LIBRARIES})

add_executable(test test.cpp)
TARGET_LINK_LIBRARIES(test PRIVATE Catch2::Catch2WithMain)