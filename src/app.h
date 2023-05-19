//
// Created by lura on 5/17/23.
//

#ifndef ALCHEMINER_APP_H
#define ALCHEMINER_APP_H

#include "AlchWindow.h"
#include "AlchPipeline.h"

namespace alchemy {

    class app {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();

    private:
        AlchWindow alchWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        AlchPipeline alchPipeline{"./shaders/simple.vert.spv", "./shaders/simple.frag.spv"};
    };

} // alchemy

#endif //ALCHEMINER_APP_H
