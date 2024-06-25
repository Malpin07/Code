include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(homeWork1 C)
set(CMAKE_C_STANDARD 11)

add_executable(homeWork1
        main.c
        io.h
        io.c
        sort.h
        sort.c
        mem.h
        mem.c
)

