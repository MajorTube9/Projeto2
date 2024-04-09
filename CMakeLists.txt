cmake_minimum_required(VERSION 3.27)
project(Projeto2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projeto2
        main.c
        tarefas.c
        tarefas.h)
