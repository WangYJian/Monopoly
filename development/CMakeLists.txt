cmake_minimum_required(VERSION 3.10)
project(development C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
aux_source_directory("." src)

add_executable(demo.exe ${src})
