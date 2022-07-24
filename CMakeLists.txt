cmake_minimum_required(VERSION 3.22)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled1 oldPr_will_be_deleted.c main.h main.c input.c input.h queue.c queue.h array.c array.h errors.c errors.h)
add_executable(nowaWersja main.c
        input.c input.h  queue.c queue.h
        errors.c errors.h
        array.c array.h charArray.c charArray.h simulation.c simulation.h)
