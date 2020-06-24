cmake_minimum_required(VERSION 3.12)
project(oop_course2_semester2_lab3)

set(CMAKE_CXX_STANDARD 14)


include_directories(Matrix)

add_executable(oop_course2_semester2_lab3 main.cpp
        Matrix/Matrix.h Matrix/Matrix.cpp
        )

