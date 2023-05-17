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
