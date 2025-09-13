#!/bin/bash

# Add git submodule
git submodule add https://github.com/glfw/glfw.git  external/glfw

# Build之前需要先 update submodule
git submodule --init --recursive

# 安装glew，本章主要讲如何链接 glew
sudo apt search glew

sudo apt install libglew-dev

# 接着在CMake中使用find_library 去找库