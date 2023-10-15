cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(multithreading)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

find_package(TBB REQUIRED)
message(STATUS "TBB_LIBRARIES = ${TBB_LIBRARIES}")

# Include the directory containing header files
include_directories(${CMAKE_SOURCE_DIR})

add_executable(main main.cpp class_singleton.cpp dining_philosophers.cpp producer_consummer.cpp)
add_executable(data_parallelism data_parallelism.cpp include/data_parallelism.h)
add_executable(std_algorithm std_algorithm.cpp include/std_algorithm.h)
add_executable(exe_policy exe_policy.cpp include/exe_policy.h)

target_link_libraries(exe_policy /usr/lib/x86_64-linux-gnu/libtbb.so)

# target_compile_definitions(main PRIVATE LOCK_GUARD_DEMO)
# target_compile_definitions(main PRIVATE THR_INTERRUPT_DEMO)
# target_compile_definitions(main PRIVATE UNIQUE_LOCK_DEMO) 
# target_compile_definitions(main PRIVATE DINING)
# target_compile_definitions(main PRIVATE SYNC)
# target_compile_definitions(main PRIVATE SYNC_COND_VAR)
# target_compile_definitions(main PRIVATE PROMISE_FUTURE) PROMISE_FUTURE_SH
# target_compile_definitions(main PRIVATE PROMISE_FUTURE_SH)
# target_compile_definitions(main PRIVATE ATOMIC)
# target_compile_definitions(main PRIVATE LOCK_FREE_QUEUE)
# target_compile_definitions(main PRIVATE PACKAGED_TASK)
target_compile_definitions(main PRIVATE ASYNC)


add_executable(assignment1 assignment1.cpp)
add_executable(assignment2 assignment2.cpp)
add_executable(assignment3 assignment3.cpp)
add_executable(assignment4 assignment4.cpp)
add_executable(assignment5 assignment5.cpp)
add_executable(assignment6 assignment6.cpp)
