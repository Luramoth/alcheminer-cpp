//
// Created by lura on 5/17/23.
//

#include "app.h"

// std
#include <array>
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
            drawFrame();
        }

        vkDeviceWaitIdle(alchDevice.device());
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

    void app::createCommandbuffers() {
        commandBuffers.resize(alchSwapChain.imageCount());

        VkCommandBufferAllocateInfo allocInfo {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = alchDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(alchDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers");
        }

        for (int i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer");
            }

            // create our render pass
            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = alchSwapChain.getRenderPass();
            renderPassInfo.framebuffer = alchSwapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = alchSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            // record the render pass to the command buffer
            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            alchPipeline->bind(commandBuffers[i]);
            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);
            // end render pass

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer");
            }
        }
    }

    void app::drawFrame() {
        uint32_t imageIndex;

        auto result = alchSwapChain.acquireNextImage(&imageIndex);
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image");
        }

        result = alchSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image");
        }
    }
} // alchemy
