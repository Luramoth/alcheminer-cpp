//
// Created by lura on 5/17/23.
//

#include "app.h"

// std
#include <stdexcept>

namespace alchemy {

    app::app() {
        createPipelineLayout();
        createpipeline();
        createCommandbuffers();
    }

    app::~app() {
        vkDestroyPipelineLayout(alchDevice.device(), pipelineLayout, nullptr);
    }

    void app::run() {
        while (!alchWindow.shouldClose()) {
            glfwPollEvents();
        }
    }

    void app::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo {};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;//
        pipelineLayoutInfo.pSetLayouts = nullptr;// pipeline set layouts send information to the  shaders that isent vertex data
        pipelineLayoutInfo.pushConstantRangeCount = 0;//
        pipelineLayoutInfo.pPushConstantRanges = nullptr;// pipeline constant ranges are an efficant way to send small bits of data to shader programs

        if (vkCreatePipelineLayout(alchDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout");
        }
    }

    void app::createpipeline() {
        auto pipelineConfig = AlchPipeline::defaultPipelineConfigInfo(alchSwapChain.width(), alchSwapChain.height());
        pipelineConfig.renderPass = alchSwapChain.getRenderPass();// renderpasses discribe the structure and format of frame buffer objects and their attachents
        pipelineConfig.pipelineLayout = pipelineLayout;
        alchPipeline = std::make_unique<AlchPipeline>(alchDevice, "shaders/simple.vert.spv", "shaders/simple.frag.spv", pipelineConfig);
    }

    void app::createCommandbuffers() {}
    void app::drawFrame() {}
} // alchemy
