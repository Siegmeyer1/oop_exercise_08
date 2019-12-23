cmake_minimum_required(VERSION 3.10)
project(OOP_lab8)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(oop_exercise_08 main.cpp figures/dot.cpp figures/octagon.cpp figures/square.cpp figures/triangle.cpp)