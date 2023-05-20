//
// Created by lura on 5/18/23.
//

#ifndef ALCHEMINER_ALCHPIPELINE_H
#define ALCHEMINER_ALCHPIPELINE_H

#include "AlchDevice.h"

#include <string>
#include <vector>

namespace alchemy {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class AlchPipeline {
    public:
        AlchPipeline(
                AlchDevice& device,
                const std::string& vertFilePath,
                const std::string& fragFilePath,
                const PipelineConfigInfo&);

        ~AlchPipeline();

        // same memory safty stuff defined in AlchWindow.h
        AlchPipeline(const AlchPipeline&) = delete;
        void operator=(const AlchPipeline&) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> readFile(const std::string filePath);

        void createGraphicsPipeline(
                const std::string& vertFilePath,
                const std::string& fragFilePath,
                const PipelineConfigInfo& configInfo);

        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

        AlchDevice& alchDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };

} // alchemy

#endif //ALCHEMINER_ALCHPIPELINE_H
