cmake_minimum_required(VERSION 2.8)
project(test_cpp11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES main.cpp)
add_executable(test_cpp11 ${SOURCE_FILES})