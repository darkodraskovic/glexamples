cmake_minimum_required(VERSION 3.8)
project (opengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Generics
include_directories("include/00_Generics")
file(GLOB GENERIC_SOURCES "src/00_Generics/*.c" "src/00_Generics/*.cpp")

# playground
add_executable(playground 00_Playground.cpp ${GENERIC_SOURCES})
target_link_libraries(playground GL GLU glfw dl)
# target_include_directories(playground PUBLIC "include/00_Generics")

# window
add_executable(window 01_Window.cpp ${GENERIC_SOURCES})
target_link_libraries(window GL GLU glfw dl)

# cube
file(GLOB CUBE_SOURCES ${GENERIC_SOURCES} "src/02_Cube/*.c" "src/02_Cube/*.cpp")
add_executable(cube 02_Cube.cpp ${CUBE_SOURCES})
target_include_directories(cube PUBLIC "include/02_Cube")
target_link_libraries(cube GL GLU glfw dl)

#camera
file(GLOB CAMERA_SOURCES ${GENERIC_SOURCES} "src/03_Camera/*.c" "src/03_Camera/*.cpp")
add_executable(camera 03_Camera.cpp ${CAMERA_SOURCES})
target_include_directories(camera PUBLIC "include/03_Camera")
target_link_libraries(camera GL GLU glfw dl)

#lighting
file(GLOB LIGHTING_SOURCES ${GENERIC_SOURCES} "src/04_Lighting/*.c" "src/04_Lighting/*.cpp")
add_executable(lighting 04_Lighting.cpp ${LIGHTING_SOURCES})
target_include_directories(lighting PUBLIC "include/04_Lighting")
target_link_libraries(lighting GL GLU glfw dl)
