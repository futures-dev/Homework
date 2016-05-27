cmake_minimum_required(VERSION 3.1)
project(Homework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")

file(GLOB SOURCE_FILES
        "KDZ/*.cpp"
        "KDZ/StringContainers/*.cpp"
        "KDZ/SimilairProviders/*.cpp"
        )

add_executable(Homework ${SOURCE_FILES})