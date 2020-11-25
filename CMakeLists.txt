cmake_minimum_required(VERSION 3.17)
project(arithmetic C)

set(CMAKE_C_STANDARD 99)

add_executable(arithmetic main.c stack.h implementation_stack.h calculate.h tokenize.h)