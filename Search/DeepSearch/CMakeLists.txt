include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(DeepSearch C)
set(CMAKE_C_STANDARD 11)

add_executable(DeepSearch DeepSearch.c
        Stack.c
        myList.h
        myList.c)



