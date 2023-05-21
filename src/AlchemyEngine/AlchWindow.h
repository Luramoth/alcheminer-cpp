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

        // prevent the AlchWindow object from being copied in any way
        AlchWindow(const AlchWindow &) = delete;// prevents the copy constructor from running
        AlchWindow &operator=(const AlchWindow &) = delete;// prevents copying of the object using the = operator

        // function is only one line so it seems ok just to make it inline
        bool shouldClose() { return glfwWindowShouldClose(window); }
        VkExtent2D getExtent() {return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};}

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        void initWindow();

        const int width;
        const int height;

        std::string windowName;
        GLFWwindow *window;
    };
} // namespace alchemy

#endif //ALCHEMINER_ALCHWINDOW_H
