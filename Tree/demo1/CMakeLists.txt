include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(treeDEMO1 C)
set(CMAKE_C_STANDARD 11)

add_executable(treeDEMO1 main.c
        demo1_QueueLink.c
        demo1_QueueLink.h)



