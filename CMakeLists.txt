cmake_minimum_required(VERSION 3.20)
project(sort C)

set(CMAKE_C_STANDARD 11)

add_executable(sort main.c sorts/sorts_.c sorts/sorts_.h nComps/comps.c nComps/comps.h)

