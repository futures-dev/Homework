cmake_minimum_required(VERSION 3.3)
project(BrokenDNA_full)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DNAElement.cpp DNARepairer.cpp)
add_executable(BrokenDNA_full ${SOURCE_FILES})