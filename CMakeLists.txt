cmake_minimum_required(VERSION 3.17)
project(arithmetic C)

set(CMAKE_C_STANDARD 11)

add_executable(arithmetic main.c declaration.h implementation_adt.h calculate.h tokenize.h implementation.h declaration.h infix_to_postfix.h)