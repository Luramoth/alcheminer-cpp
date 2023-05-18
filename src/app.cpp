//
// Created by lura on 5/17/23.
//

#include "app.h"

namespace alchemy {

    void app::run() {
        while (!alchWindow.shouldClose()) {
            glfwPollEvents();
        }
    }
} // alchemy