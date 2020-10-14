cmake_minimum_required(VERSION 3.16)
project(sections)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(sections main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(sections OpenMP::OpenMP_CXX)
endif()