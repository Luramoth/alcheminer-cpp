cmake_minimum_required(VERSION 3.25)
project(alcheminer)

set(CMAKE_CXX_STANDARD 17)

# Genorate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Grab OGRE as a dependency
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

# set the build directory to build/
if(NOT EXISTS ${CMAKE_BINARY_DIR})
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

#find libraries
find_package(glfw3 3.3 REQUIRED)

# make project executable
add_executable(${PROJECT_NAME} src/main.cpp)

# includes ogre and its dependencies
target_link_libraries(${PROJECT_NAME} OgreBites)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build )

# Set the path to the Clang compiler
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")