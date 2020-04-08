# OpenGL Examples

## Installation

First install debian based Linux distro :)

On Ubuntu, install the following libraries:

```
apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev libxi-dev
```

Install [Glad library](https://github.com/Dav1dde/glad.git), a GL/GLES/EGL/GLX/WGL Loader-Generator:

```
git clone https://github.com/Dav1dde/glad.git 
cd glad 
cmake ./ 
make 
sudo cp -a include /usr/local/
```

Copy *glad.c* from *glad/src/* git cloned source directory to the project *source/* directory. 

Install [STB library](https://github.com/nothings/stb) for image handling:

```
git clone https://github.com/nothings/stb.git 
cd stb 
cp -a stb* /usr/local/include/
```

## Target link libraries for CMake

A list of all the used libraries for examples.

```target_link_libraries(main GL GLU glfw X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp)```

## Build

In order to compile a specific example, `mkdir build`, `cd build` and run

```cmake ../```

After the successful creation of the *Makefile* build the examples with

```make <example> && ./example```

where <example> stands for the name of `.cpp` file stripped of number prefix
(e.g. "02") and extension ".cpp". E.g. to make and run *01_window.cpp* run

```make window && ./window```
