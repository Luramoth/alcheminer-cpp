# Alcheminer
[![wakatime](https://wakatime.com/badge/user/58d443b6-e6af-4fa2-9946-c53ddafb5a4f/project/a17ac659-6a26-4893-8655-03252be75761.svg)](https://wakatime.com/badge/user/58d443b6-e6af-4fa2-9946-c53ddafb5a4f/project/a17ac659-6a26-4893-8655-03252be75761)
![GitHub repo size](https://img.shields.io/github/repo-size/Luramoth/alcheminer-cpp)
![GitHub last commit](https://img.shields.io/github/last-commit/Luramoth/alcheminer-cpp)

## development deps:

### ubuntu:
`sudo apt install vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools libglfw3-dev libglm-dev libxxf86vm-dev libxi-dev`

### fedora/RHEL:
`sudo dnf install vulkan-tools vulkan-loader-devel esa-vulkan-devel vulkan-validation-layers-devel glfw-devel glm-devel glslc libXi-devel libXxf86vm-devel`

### Arch:
`sudo pacman -S vulkan-devel glfw-wayland glfw-x11 glm shaderc libxi libxxf86vm`

## building:
before using cmake to compile the whole program vulkan requires that the shaders get
compiled, it's recommended you use glslc and execute the bash script `shade_compile.sh`

### on ubuntu:
download glslc through [this link](https://github.com/google/shaderc#downloads) from the official
glslc GitHub repo
