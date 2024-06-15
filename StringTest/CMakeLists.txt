include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(StringTest C)
set(CMAKE_C_STANDARD 11)

add_executable(StringTest main.c
        mystring.c)



