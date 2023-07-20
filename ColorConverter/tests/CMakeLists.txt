cmake_minimum_required(VERSION 3.5)

project(ColorConverterTests LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(
    ColorConverterTests
    main.c
    ../utils.h
    ../utils.c
)
