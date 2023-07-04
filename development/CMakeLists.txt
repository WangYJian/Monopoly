cmake_minimum_required(VERSION 3.22)
project(development C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
include_directories(.)

add_executable(development
        Game.c
        Game.h
        Map.c
        Map.h
        Player.c
        Player.h
        Property.c
        Property.h
        Tool.c
        Tool.h main.c Judge.c)

