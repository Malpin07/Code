include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(DblStack C)
set(CMAKE_C_STANDARD 11)

add_executable(DblStack DblStack.c
        main.c
        DblStack.h)



