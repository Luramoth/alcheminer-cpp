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