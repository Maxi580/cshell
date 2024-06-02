cmake_minimum_required(VERSION 3.10)
project(cshell  C)

set(CMAKE_C_STANDARD 99)

add_executable(cshell  main.c
        builtins.h)