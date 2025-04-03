cmake_minimum_required(VERSION 3.0)

project(maze_runner CXX)  # Especificando que o projeto usa C++

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE maze_runner.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
