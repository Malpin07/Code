include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(LinkList C)
set(CMAKE_C_STANDARD 11)

add_executable(LinkList
        myList.c
        LinkList.c
)

