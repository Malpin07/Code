include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(homework4 C)
set(CMAKE_C_STANDARD 11)
add_executable(homework4 main.c
        SequenceList.c)
