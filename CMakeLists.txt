# Ad Maiorem Dei Gloriam!
cmake_minimum_required(VERSION 3.10)
project(CPaint C)

set(C_STANDARD_REQUIRED 11)
set(SRC src/main.c)

# TODO: change to fetch-content
find_package(raylib REQUIRED)

add_executable(CPaint)
target_sources(CPaint PRIVATE ${SRC})
target_include_directories(CPaint PRIVATE include/)
target_link_libraries(CPaint PRIVATE raylib)
