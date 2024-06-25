include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(TwoForkTree C)
set(CMAKE_C_STANDARD 11)

add_executable(TwoForkTree main.c
        Stack.c
)



