cmake_minimum_required(VERSION 3.0)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c17 -Wall -Wextra -Wno-implicit-fallthrough")


add_executable(nowaWersja labirinth.c
        input.c input.h  queue.c queue.h
        errors.c errors.h
        array.c array.h charArray.c charArray.h simulation.c simulation.h array.h)
