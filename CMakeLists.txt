cmake_minimum_required(VERSION 3.8)
project (opengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(INCLUDE "include")
set(SOURCE "source")
set(LIB "00_Generics")

# Generics
include_directories("${INCLUDE}/${LIB}")
file(GLOB SOURCES "${SOURCE}/*.c" "${SOURCE}/*.cpp")

# playground
add_executable(playground 00_Playground.cpp ${SOURCES})
target_link_libraries(playground GL GLU glfw dl)

# window
add_executable(window 01_Window.cpp ${SOURCES})
target_link_libraries(window GL GLU glfw dl)

# cube
file(GLOB CUBE_SOURCES ${SOURCES} "${SOURCE}/02_Cube/*.c" "${SOURCE}/02_Cube/*.cpp")
add_executable(cube 02_Cube.cpp ${CUBE_SOURCES})
target_include_directories(cube PUBLIC "${INCLUDE}/02_Cube")
target_link_libraries(cube GL GLU glfw dl)

#camera
file(GLOB CAMERA_SOURCES ${SOURCES} "${SOURCE}/03_Camera/*.c" "${SOURCE}/03_Camera/*.cpp")
add_executable(camera 03_Camera.cpp ${CAMERA_SOURCES})
target_include_directories(camera PUBLIC "${INCLUDE}/03_Camera")
target_link_libraries(camera GL GLU glfw dl)

#lighting
file(GLOB LIGHTING_SOURCES ${SOURCES} "${SOURCE}/04_Lighting/*.c" "${SOURCE}/04_Lighting/*.cpp")
add_executable(lighting 04_Lighting.cpp ${LIGHTING_SOURCES})
target_include_directories(lighting PUBLIC "${INCLUDE}/04_Lighting")
target_link_libraries(lighting GL GLU glfw dl)

#lighting
file(GLOB TEXTURES_SOURCES ${SOURCES} "${SOURCE}/05_Textures/*.c" "${SOURCE}/05_Textures/*.cpp")
add_executable(textures 05_Textures.cpp ${TEXTURES_SOURCES})
target_include_directories(textures PUBLIC "${INCLUDE}/05_Textures")
target_link_libraries(textures GL GLU glfw dl)
