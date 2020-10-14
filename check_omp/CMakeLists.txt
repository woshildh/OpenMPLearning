cmake_minimum_required(VERSION 3.16)
project(check_omp)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenMP)

add_executable(check_omp main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(check_omp OpenMP::OpenMP_CXX)
endif()