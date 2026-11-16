# Ad Maiorem Dei Gloriam!
cmake_minimum_required(VERSION 3.10)
project(CPaint C)

set(C_STANDARD_REQUIRED 11)
set(SRC external/raygui.c src/main.c src/canvas.c src/history.c src/filedialogue.c)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# TODO: change to fetch-content
find_package(raylib REQUIRED)

add_executable(CPaint)
target_sources(CPaint PRIVATE ${SRC})
target_include_directories(CPaint PRIVATE include/ external/)
target_link_libraries(CPaint PRIVATE raylib)
