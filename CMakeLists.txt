cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(multithreading)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

# Include the directory containing header files
include_directories(${CMAKE_SOURCE_DIR})

add_executable(main main.cpp class_singleton.cpp dining_philosophers.cpp)

# target_compile_definitions(main PRIVATE LOCK_GUARD_DEMO)
# target_compile_definitions(main PRIVATE THR_INTERRUPT_DEMO)
# target_compile_definitions(main PRIVATE UNIQUE_LOCK_DEMO) 
target_compile_definitions(main PRIVATE DINING)

add_executable(assignment1 assignment1.cpp)
add_executable(assignment2 assignment2.cpp)
add_executable(assignment3 assignment3.cpp)
