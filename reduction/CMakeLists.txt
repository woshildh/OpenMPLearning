cmake_minimum_required(VERSION 3.16)
project(reduction)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(reduction main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(reduction OpenMP::OpenMP_CXX)
endif()