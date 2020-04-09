cmake_minimum_required(VERSION 3.8)
project (opengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDE "include")
set(INCLUDE_ENGINE "${INCLUDE}/engine")
set(INCLUDE_SAMPLES "${INCLUDE}/samples")
set(SOURCE "source")
set(SOURCE_ENGINE "${SOURCE}/engine")
set(SOURCE_SAMPLES "${SOURCE}/samples")

# Generics
include_directories("${INCLUDE_ENGINE}")
file(GLOB SOURCE_ENGINE_C "${SOURCE_ENGINE}/*.c" "${SOURCE}/*.cpp")

# playground
add_executable(playground 00_Playground.cpp ${SOURCE_ENGINE_C})
target_link_libraries(playground GL GLU glfw dl)

# window
add_executable(window 01_Window.cpp ${SOURCE_ENGINE_C})
target_link_libraries(window GL GLU glfw dl)

# cube
file(GLOB CUBE_SOURCES ${SOURCE_ENGINE_C} "${SOURCE_SAMPLES}/02_Cube/*.cpp")
add_executable(cube 02_Cube.cpp ${CUBE_SOURCES})
target_include_directories(cube PUBLIC "${INCLUDE_SAMPLES}/02_Cube")
target_link_libraries(cube GL GLU glfw dl)

# camera
file(GLOB CAMERA_SOURCES ${SOURCE_ENGINE_C} "${SOURCE_SAMPLES}/03_Camera/*.cpp")
add_executable(camera 03_Camera.cpp ${CAMERA_SOURCES})
target_include_directories(camera PUBLIC "${INCLUDE_SAMPLES}/03_Camera")
target_link_libraries(camera GL GLU glfw dl)

# lighting
file(GLOB LIGHTING_SOURCES ${SOURCE_ENGINE_C} "${SOURCE_SAMPLES}/04_Lighting/*.cpp")
add_executable(lighting 04_Lighting.cpp ${LIGHTING_SOURCES})
target_include_directories(lighting PUBLIC "${INCLUDE_SAMPLES}/04_Lighting")
target_link_libraries(lighting GL GLU glfw dl)

# textures
file(GLOB TEXTURES_SOURCES ${SOURCE_ENGINE_C} "${SOURCE_SAMPLES}/05_Textures/*.cpp")
add_executable(textures 05_Textures.cpp ${TEXTURES_SOURCES})
target_include_directories(textures PUBLIC "${INCLUDE_SAMPLES}/05_Textures")
target_link_libraries(textures GL GLU glfw dl)

# entity
file(GLOB ENTITY_SOURCES ${SOURCE_ENGINE_C} "${SOURCE_SAMPLES}/06_Entity/*.cpp")
add_executable(entity 06_Entity.cpp ${ENTITY_SOURCES})
target_include_directories(entity PUBLIC "${INCLUDE_SAMPLES}/06_Entity")
target_link_libraries(entity GL GLU glfw dl)
