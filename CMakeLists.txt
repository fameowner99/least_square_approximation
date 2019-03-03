cmake_minimum_required(VERSION 3.13)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

find_library(libsdl SDL2)

add_executable(lab1
        main.cpp lab1.cpp
        Matrix.cpp)
target_link_libraries(lab1 ${libsdl})
