cmake_minimum_required(VERSION 3.9)
project(include/AutoDiff)

set(CMAKE_CXX_STANDARD 11)


include_directories(include)

set(DEMO_FILES main.cpp)

add_executable(Demo ${DEMO_FILES})