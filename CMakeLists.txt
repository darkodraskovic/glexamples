cmake_minimum_required(VERSION 3.8)
project (opengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB SOURCES "src/*.c" "src/*.cpp")

add_executable(playground 00_Playground.cpp ${SOURCES})
add_executable(window 01_Window.cpp ${SOURCES})
add_executable(cube 02_Cube.cpp ${SOURCES})

target_link_libraries(playground GL GLU glfw dl)
target_link_libraries(window GL GLU glfw dl)
target_link_libraries(cube GL GLU glfw dl)
