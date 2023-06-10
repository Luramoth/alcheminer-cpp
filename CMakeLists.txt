cmake_minimum_required(VERSION 3.25)
project(alcheminer)

set(CMAKE_CXX_STANDARD 11)

# Genorate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# make project executable
add_executable(${PROJECT_NAME} src/main.cpp
        src/glad.c
        src/include/glad/glad.h
        src/include/KHR/khrplatform.h)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)

# Set the path to the Clang compiler
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# if in release have the shaders path be relative to the executable, otherwise to the dev mechine
if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
    target_compile_definitions(${PROJECT_NAME} PUBLIC ALCH_SHADERS_PATH="./shaders")
else ()
    target_compile_definitions(${PROJECT_NAME} PUBLIC ALCH_SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")
endif ()