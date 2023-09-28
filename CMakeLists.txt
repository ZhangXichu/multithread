cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(multithreading)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

# Include the directory containing header files
include_directories(${CMAKE_SOURCE_DIR})

add_executable(main main.cpp class_singleton.cpp)
add_executable(assignment1 assignment1.cpp)
add_executable(assignment2 assignment2.cpp)
