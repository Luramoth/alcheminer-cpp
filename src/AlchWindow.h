//
// Created by lura on 5/17/23.
//

#ifndef ALCHEMINER_ALCHWINDOW_H
#define ALCHEMINER_ALCHWINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace alchemy {
    class AlchWindow {
    public:
        AlchWindow(int w, int h, std::string name);
        ~AlchWindow();

        // some memory safety I don't fully understand
        AlchWindow(const AlchWindow &) = delete;
        AlchWindow &operator=(const AlchWindow &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }

    private:
        void initWindow();

        const int width;
        const int height;

        std::string windowName;
        GLFWwindow *window;
    };
} // namespace alchemy

#endif //ALCHEMINER_ALCHWINDOW_H
