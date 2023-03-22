cmake_minimum_required(VERSION 3.22)
project(conwaysGameOfLife)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(conwaysGameOfLife main.cpp)


find_package(OpenMP)

message(STATUS "COMPILED BINARY AT ${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main)

if(OpenMP_CXX_FOUND)
    message(STATUS "OPENMP FOUND")
    target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
endif()