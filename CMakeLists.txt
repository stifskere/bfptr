cmake_minimum_required(VERSION 3.28)
project(bfptr C)

set(CMAKE_C_STANDARD 11)

add_library(bfptr STATIC src/bfptr.c)
