cmake_minimum_required(VERSION 3.22)
project(development C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(development.exe
        Game.c
        Game.h
        Judge.c
        Judge.h
        main.c
        Map.c
        Map.h
        Player.c
        Player.h
        Property.c
        Property.h
        Tool.c
        Tool.h)
