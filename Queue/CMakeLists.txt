include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(Queue C)
set(CMAKE_C_STANDARD 11)

add_executable(Queue
        Queue.c
        main.c
        Queue.h
)

