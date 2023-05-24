cmake_minimum_required(VERSION 3.25)
project(alcheminer)

set(CMAKE_CXX_STANDARD 11)

# Genorate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 4.2.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# set the build directory to build/
if(NOT EXISTS ${CMAKE_BINARY_DIR})
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# make project executable
add_executable(${PROJECT_NAME} src/main.cpp)

# includes ogre and its dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build )

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Set the path to the Clang compiler
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")