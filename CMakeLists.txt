cmake_minimum_required(VERSION 3.30)

find_package(PkgConfig)

project(Breakout LANGUAGES C)

pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(breakout src/glad.c src/main.c)

set_property(TARGET breakout PROPERTY C_EXTENSIONS OFF)
set_property(TARGET breakout PROPERTY C_STANDARD 99)

target_compile_definitions(breakout PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(breakout PRIVATE include)
target_link_libraries(breakout PRIVATE ${GLFW_LIBRARIES})
