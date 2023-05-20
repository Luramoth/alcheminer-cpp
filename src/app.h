//
// Created by lura on 5/17/23.
//

#ifndef ALCHEMINER_APP_H
#define ALCHEMINER_APP_H

#include "AlchemyEngine/AlchDevice.h"
#include "AlchemyEngine/AlchPipeline.h"
#include "AlchemyEngine/AlchWindow.h"

namespace alchemy {

    class app {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();

    private:
        AlchWindow alchWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        AlchDevice alchDevice{alchWindow};
        AlchPipeline alchPipeline{alchDevice,"./shaders/simple.vert.spv", "./shaders/simple.frag.spv", AlchPipeline::defaultPipelineConfigInfo(WIDTH,HEIGHT)};
    };

} // alchemy

#endif //ALCHEMINER_APP_H
