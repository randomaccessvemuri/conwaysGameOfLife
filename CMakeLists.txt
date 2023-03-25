cmake_minimum_required(VERSION 3.22)
project(conwaysGameOfLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(conwaysGameOfLife main.cpp generation.h generation.cpp)

find_package(SDL2 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenMP)
find_package(Boost REQUIRED)

message(STATUS "COMPILED BINARY AT ${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main boost_program_options ${OpenCV_LIBS})

if(OpenMP_CXX_FOUND)
    message(STATUS "OPENMP FOUND")
    target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
endif()