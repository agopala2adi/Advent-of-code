
cmake_minimum_required(VERSION 3.18)
project(my_project LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Point to OR-Tools install directory
list(APPEND CMAKE_PREFIX_PATH "ortools")

find_package(ortools REQUIRED)

add_executable(day10soln solution.cpp)
target_link_libraries(day10soln PRIVATE ortools::ortools)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
