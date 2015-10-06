cmake_minimum_required(VERSION 3.3)
project(Homework3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Homework3/RadixSort.cpp Homework3/RadixSort.h)
add_executable(Homework3 ${SOURCE_FILES} Homework3/RadixSort.cpp Homework3/RadixSort.h)