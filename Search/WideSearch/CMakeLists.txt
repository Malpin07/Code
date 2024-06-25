include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(WideSearch C)
set(CMAKE_C_STANDARD 11)

add_executable(WideSearch WideSearch.c
        myQueue.c
        myQueue.h
)



