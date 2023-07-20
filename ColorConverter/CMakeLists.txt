cmake_minimum_required(VERSION 3.5)

project(ColorConverter LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(
    ColorConverter
    main.c
    utils.c
    utils.h
)

add_subdirectory(tests)

install(TARGETS ColorConverter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
