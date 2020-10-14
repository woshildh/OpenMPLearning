cmake_minimum_required(VERSION 3.16)
project(schedule)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(schedule main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(schedule OpenMP::OpenMP_CXX)
endif()