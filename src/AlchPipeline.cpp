//
// Created by lura on 5/18/23.
//

#include "AlchPipeline.h"
#include <fstream>
#include <iostream>

namespace alchemy {
    AlchPipeline::AlchPipeline(AlchDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo) : alchDevice{device} {

        createGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
    }

    std::vector<char> AlchPipeline::readFile(const std::string filePath) {
        // open file and go to the end and specify that it's binary
        std::ifstream file{filePath, std::ios::ate | std::ios::binary};

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file: " + filePath);
        }

        // get the size of the file
        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize); // make character buffer

        file.seekg(0);// return to the start of the file
        file.read(buffer.data(), fileSize);// read the contents of the file and put it into the buffer

        file.close();// close the file
        return buffer;
    }

    void AlchPipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo) {

        // read out shader code
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "Vertex shader file size: " << vertCode.size() << '\n';
        std::cout << "Fragment shader file size: " << fragCode.size() << '\n';
    }

    void AlchPipeline::createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        if (vkCreateShaderModule(alchDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS){
            throw std::runtime_error("failed to create shader module");
        }
    }

    PipelineConfigInfo AlchPipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }
} // alchemy