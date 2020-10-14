cmake_minimum_required(VERSION 3.16)
project(single)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(single main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(single OpenMP::OpenMP_CXX)
endif()