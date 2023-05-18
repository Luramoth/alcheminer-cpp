//
// Created by lura on 5/17/23.
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "AlchWindow.h"

namespace alchemy {
    AlchWindow::AlchWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
        initWindow();
    }

    AlchWindow::~AlchWindow() {
        glfwDestroyWindow(window);// destroy and deallocate the window
        glfwTerminate();// get glfw to shove off
    }

    void AlchWindow::initWindow() {
        // initialaise glfw
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);// tell it to not use OpenGL
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);// tell it not to make the window resizable

        // create the window
        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }
}// namespace alchemy