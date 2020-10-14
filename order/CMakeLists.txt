cmake_minimum_required(VERSION 3.16)
project(ordered)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(ordered main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(ordered OpenMP::OpenMP_CXX)
endif()