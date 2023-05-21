//
// Created by lura on 5/17/23.
//

#ifndef ALCHEMINER_APP_H
#define ALCHEMINER_APP_H

#include "AlchemyEngine/AlchDevice.h"
#include "AlchemyEngine/AlchPipeline.h"
#include "AlchemyEngine/AlchSwapChain.h"
#include "AlchemyEngine/AlchWindow.h"

//std
#include <memory>
#include <vector>

namespace alchemy {

    class app {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        app();
        ~app();

        app(const app &) = delete;// prevents the copy constructor from running
        app &operator=(const app &) = delete;// prevents copying of the object using the = operator

        void run();

    private:
        void createPipelineLayout();
        void createpipeline();
        void createCommandbuffers();
        void drawFrame();

        AlchWindow alchWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        AlchDevice alchDevice{alchWindow};
        AlchSwapChain alchSwapChain{alchDevice, alchWindow.getExtent()};
        std::unique_ptr<AlchPipeline> alchPipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };

} // alchemy

#endif //ALCHEMINER_APP_H
