cmake_minimum_required(VERSION 3.16.3)
project(grepx)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

find_package(Threads)


include_directories(./)
add_executable(grepx grep_ex.cpp)

