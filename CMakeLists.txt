cmake_minimum_required(VERSION 3.3)
project(Homework4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Homework4/merge_sort.cpp Homework4/merge_sort.h)
add_executable(Homework4 ${SOURCE_FILES} Homework4/merge_sort.cpp Homework4/merge_sort.h)