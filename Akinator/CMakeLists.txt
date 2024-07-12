cmake_minimum_required(VERSION 3.26)
project(treekinator C)

set(CMAKE_C_STANDARD 23)

add_executable(treekinator main.c
        tree.h)
