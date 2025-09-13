#! /bin/bash

# Add git submodule
git submodule add https://github.com/glfw/glfw.git  external/glfw

# Build之前需要先 update submodule
git submodule update --init --recursive