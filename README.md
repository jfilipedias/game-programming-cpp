# Game Progamming In C++

This repository contains the code examples and exercises from the book "Game Programming in C++". The book covers
various topics related to game development, including graphics, physics, and AI. The book build the projects using the
library SDL2, but I decided to use the library SDL3. Furthermore, the author uses GLEW with OpenGL 3.3, although I
choose
to use Glad with OpenGL 4.1, the last version with support on MacOS.

## Getting Started

To build the project, make sure you have [CMake](https://cmake.org) 3.24 or later installed.

Once the project use vendored libraries as git submodule, you need to initialize the libraries with the following
command:

```sh
git submodule update --init --recursive
```

Inside a project directory, build the project with the following command:

```sh
cd chapter01
cmake -S . -B build
cmake --build build
```
