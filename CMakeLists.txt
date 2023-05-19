cmake_minimum_required(VERSION 3.25)
project(alcheminer)

set(CMAKE_CXX_STANDARD 17)

#find libraries
find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)

# make project executable
add_executable(alcheminer src/main.cpp
        src/AlchWindow.cpp
        src/AlchWindow.h
        src/app.cpp
        src/app.h
        src/AlchPipeline.cpp
        src/AlchPipeline.h
        src/AlchDevice.cpp)

# link libraries
target_link_libraries(alcheminer PRIVATE glfw Vulkan::Vulkan)