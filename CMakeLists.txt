cmake_minimum_required(VERSION 4.1)
project(16-Bit-Computer-simulator C)

set(CMAKE_C_STANDARD 11)

add_executable(16-Bit-Computer-simulator  CPU.c
        prime.c
        prime.h
        hash_table.c
        hash_table.h)
