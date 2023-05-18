#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class app {
public:
    GLFWwindow* window;

    void run() {
        initWindow();
        init();
        mainLoop();
        cleanup();
    }
private:
    VkInstance instance;

    void initWindow() {
        glfwInit();

        // tell openGL not to use OpenGL
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // then make the window not resizable
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // create the window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Alcheminer", nullptr, nullptr);
    }

    void init() {
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }

    ///////// extra funcs

    void createInstance() {
        //// application info (optional I think)
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "alcheminer";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        ////

        //// instance info, not optional
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // GLFW extension info for Vulkan to interface
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // layers
        createInfo.enabledLayerCount = 0;
        ////

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance!");
        }
    }
};

int main() {
    app App{};

    try {
        App.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
