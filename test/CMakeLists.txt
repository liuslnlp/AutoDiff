cmake_minimum_required(VERSION 3.5)
project(ADTest)

set(CMAKE_CXX_STANDARD 11)

include_directories(../include)

set(ADTest_FILES test_ad.cpp)

add_executable(ADTest ${ADTest_FILES})