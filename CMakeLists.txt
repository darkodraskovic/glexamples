cmake_minimum_required(VERSION 3.8)
project (opengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

set(SOURCE_FILES_PLAYGROUND glad.c 00_playground.cpp)
set(SOURCE_FILES_WINDOW glad.c 01_window.cpp)
set(SOURCE_FILES_CUBE glad.c 02_cube.cpp)

add_executable(playground ${SOURCE_FILES_PLAYGROUND})
add_executable(window ${SOURCE_FILES_WINDOW})
add_executable(cube ${SOURCE_FILES_CUBE})

target_link_libraries(playground GL GLU glfw dl)
target_link_libraries(window GL GLU glfw dl)
target_link_libraries(cube GL GLU glfw dl)