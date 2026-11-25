# Ad Maiorem Dei Gloriam!
cmake_minimum_required(VERSION 3.10)
project(CPaint C)

set(C_STANDARD_REQUIRED 11)
set(SRC external/raygui.c src/main.c src/canvas.c src/history_buffer.c src/gui.c src/viewport.c)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# TODO: change to fetch-content
find_package(raylib REQUIRED)

include(FetchContent)
FetchContent_Declare(
    nvdialog
    GIT_REPOSITORY https://github.com/tseli0s/nvdialog.git
    GIT_TAG master
)
FetchContent_MakeAvailable(nvdialog)

add_executable(CPaint)
target_sources(CPaint PRIVATE ${SRC})
target_include_directories(CPaint PRIVATE include/ external/)
target_link_libraries(CPaint PRIVATE raylib) #nvdialog)
