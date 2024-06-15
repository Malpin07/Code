cmake_minimum_required(VERSION 3.28)
project(C_Code C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Code main.c)

ADD_SUBDIRECTORY(LinkList)
ADD_SUBDIRECTORY(FileDemo)
ADD_SUBDIRECTORY(TestBinary)
ADD_SUBDIRECTORY(DoubleLinkedList)
ADD_SUBDIRECTORY(Sort/PopSort)
ADD_SUBDIRECTORY(Sort/SelectSort)
ADD_SUBDIRECTORY(Sort/QuickSort)
ADD_SUBDIRECTORY(Search/BinarySearch)
ADD_SUBDIRECTORY(StringTest)