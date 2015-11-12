cmake_minimum_required(VERSION 3.3)
project(Homework7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Homework7/linked_list.cpp Homework7/linked_list.h Homework7/main.cpp)
add_executable(Homework7 ${SOURCE_FILES})