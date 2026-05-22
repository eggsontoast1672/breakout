cmake_minimum_required(VERSION 3.30)

find_package(PkgConfig)

project(Breakout LANGUAGES C)

pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(
    breakout
    src/glad.c
    src/logging.c
    src/main.c
    src/render.c
    src/shader.c
    src/texture.c
    src/window.c
)

set_property(TARGET breakout PROPERTY C_EXTENSIONS OFF)
set_property(TARGET breakout PROPERTY C_STANDARD 99)

target_compile_definitions(breakout PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(breakout PRIVATE -Wall -Werror -Wextra)
target_include_directories(breakout PRIVATE include)
target_link_libraries(breakout PRIVATE m ${GLFW_LIBRARIES})
