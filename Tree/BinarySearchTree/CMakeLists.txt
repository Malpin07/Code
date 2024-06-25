include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(BinarySearchTree C)
set(CMAKE_C_STANDARD 11)

add_executable(BinarySearchTree main.c
        BinarySearchTree.c
        BinarySearchTree.h

)



