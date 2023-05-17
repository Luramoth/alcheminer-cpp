#include "Engine/engine.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {

    try {
        Engine::engine::run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
