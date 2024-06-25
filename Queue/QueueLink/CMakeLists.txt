include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(QueueLink C)
set(CMAKE_C_STANDARD 11)

add_executable(QueueLink
        main.c
        QueueLink.c
        QueueLink.h
)

