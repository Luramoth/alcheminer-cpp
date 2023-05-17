//
// Created by lura on 5/17/23.
//

#include "engine.h"
#include "renderer.h"

namespace Engine {
    void engine::run() {
        engine::init();
        engine::mainLoop();
        engine::cleanup();
    }

    void engine::init() {
        renderer::initVulkan();
    }

    void engine::mainLoop() {
        renderer::update();
    }

    void engine::cleanup() {
        renderer::cleanup();
    }
} // Engine