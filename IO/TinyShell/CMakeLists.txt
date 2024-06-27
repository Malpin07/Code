include_directories(.)

cmake_minimum_required(VERSION 3.28)
project(mockCMD C)

set(CMAKE_C_STANDARD 11)

add_executable(mockCMD main.c
        cmd_cp.c
        cmd_handle.c
        cmd_ls.c
       )
