cmake_minimum_required(VERSION 3.3)
project(Homework7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Homework8/block_searcher.cpp Homework8/edge_searcher.cpp Homework8/block_searcher.h Homework8/edge_searcher.h Homework8/main.cpp)
add_executable(Homework8 ${SOURCE_FILES})