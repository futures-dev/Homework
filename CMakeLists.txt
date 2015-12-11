cmake_minimum_required(VERSION 3.3)
project(KDZ)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES KDZ/main.cpp KDZ/KnapsackSolver.cpp KDZ/KnapsackSolver.h KDZ/KnapsackTester.cpp KDZ/KnapsackTester.h)
add_executable(KDZ ${SOURCE_FILES})