cmake_minimum_required(VERSION 3.26)
project(All_C C)

set(CMAKE_C_STANDARD 11)

add_library(All_C SHARED library.c
        List/queue.c
        include/queue.h
        include/data.h
        include/tree.h
        Graph/tree.c)
