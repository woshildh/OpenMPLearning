cmake_minimum_required(VERSION 3.16)
project(parallel)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(parallel parallel.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(parallel OpenMP::OpenMP_CXX)
endif()