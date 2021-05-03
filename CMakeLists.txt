
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

project(mnet)

add_library(mnet
    src/mnet.c
    src/marp.c
    src/mether.c
    src/mmem.c
    src/mtcp.c)
