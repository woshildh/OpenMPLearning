cmake_minimum_required(VERSION 3.16)
project(nested)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(nested main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(nested OpenMP::OpenMP_CXX)
endif()