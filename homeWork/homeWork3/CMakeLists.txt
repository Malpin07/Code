include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(homeWork3 C)
set(CMAKE_C_STANDARD 11)

add_executable(homeWork3
        main.c
        student.h
        student.c
        controller.c
        controller.h

)

