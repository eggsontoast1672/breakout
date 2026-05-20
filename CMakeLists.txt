cmake_minimum_required(VERSION 3.30)

project(Breakout LANGUAGES C)

add_executable(breakout src/main.c)

set_property(TARGET breakout PROPERTY C_EXTENSIONS OFF)
set_property(TARGET breakout PROPERTY C_STANDARD 99)
