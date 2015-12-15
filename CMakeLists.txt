cmake_minimum_required(VERSION 3.1)
project(Homework12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Homework12/main.cpp)
add_executable(KDZ ${SOURCE_FILES})