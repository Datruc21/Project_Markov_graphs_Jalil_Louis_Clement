cmake_minimum_required(VERSION 3.27)
project(2526_TI301_PJT C)

set(CMAKE_C_STANDARD 11)

add_executable(TI_301_PJT
        main.c utils.c
        matrix.c
        matrix.h)

add_executable(TI_301_PJT_part2
        main2.c utils.c hasse.c
        matrix.c
        matrix.h)