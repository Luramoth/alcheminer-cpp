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

        // specify how to assemble geometry
        configInfo.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        configInfo.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        configInfo.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

        // configure the viewport (describes the transformation between the pipeline output and the target image)
        configInfo.viewport.x = 0.0f;
        configInfo.viewport.y = 0.0f;
        configInfo.viewport.width = static_cast<float>(width);
        configInfo.viewport.height = static_cast<float>(height);
        configInfo.viewport.minDepth = 0.0f;
        configInfo.viewport.maxDepth = 1.0f;

        // the scissor is kind of like the viewport in a way but it discards pixels outside of the viewport instead of squishes them
        configInfo.scissor.offset = {0, 0};
        configInfo.scissor.extent = {width, height};

        // bundle the viewport and scissor together in a vulkan struct
        configInfo.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        configInfo.viewportInfo.viewportCount = 1;
        configInfo.viewportInfo.pViewports = &configInfo.viewport;
        configInfo.viewportInfo.scissorCount = 1;
        configInfo.viewportInfo.pScissors = &configInfo.scissor;

        // this breaks up the geometry into fragments for each pixel the triangle overlaps
        configInfo.rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        configInfo.rasterizationInfo.depthClampEnable = VK_FALSE; // prevent verts from being clamped and  let them go in front of or behind the camera
        configInfo.rasterizationInfo.rasterizerDiscardEnable = VK_FALSE; // make it so all primitives arent just thrown away before rasterisation
        configInfo.rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL; // make triangles solid
        configInfo.rasterizationInfo.lineWidth = 1.0f;
        configInfo.rasterizationInfo.cullMode = VK_CULL_MODE_NONE; // dissabled for now for debug porposees
        configInfo.rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE; // see what side of a triangle we are seeing based on the order that verts are established without normals
        configInfo.rasterizationInfo.depthBiasEnable = VK_FALSE; // wont be used for now, keeping it dissabled
        configInfo.rasterizationInfo.depthBiasConstantFactor = 0.0f; // optional
        configInfo.rasterizationInfo.depthBiasClamp = 0.0f; // optional
        configInfo.rasterizationInfo.depthBiasSlopeFactor = 0.0f; // optional

        // get MSAA working
        configInfo.multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        configInfo.multisampleInfo.sampleShadingEnable = VK_FALSE;
        configInfo.multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        configInfo.multisampleInfo.minSampleShading = 1.0f; // optional
        configInfo.multisampleInfo.pSampleMask = nullptr; // optional
        configInfo.multisampleInfo.alphaToCoverageEnable = VK_FALSE; // optional
        configInfo.multisampleInfo.alphaToOneEnable = VK_FALSE; // optional

        // color blending defines how colors are combined in the frame buffer (helps with transparency)
        configInfo.colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        configInfo.colorBlendAttachment.blendEnable = VK_FALSE;
        configInfo.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // optional
        configInfo.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // optional
        configInfo.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // optional
        configInfo.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // optional
        configInfo.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // optional
        configInfo.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // optional

        configInfo.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        configInfo.colorBlendInfo.logicOpEnable = VK_FALSE;
        configInfo.colorBlendInfo.logicOp = VK_LOGIC_OP_COPY; // optional
        configInfo.colorBlendInfo.attachmentCount = 1;
        configInfo.colorBlendInfo.pAttachments = &configInfo.colorBlendAttachment;
        configInfo.colorBlendInfo.blendConstants[0] = 0.0f; // optional
        configInfo.colorBlendInfo.blendConstants[1] = 0.0f; // optional
        configInfo.colorBlendInfo.blendConstants[2] = 0.0f; // optional
        configInfo.colorBlendInfo.blendConstants[3] = 0.0f; // optional

        // depth buffer stores depth information on each fragment (pixel) dark shades being close by and light shades being far away
        configInfo.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        configInfo.depthStencilInfo.depthTestEnable = VK_TRUE;
        configInfo.depthStencilInfo.depthWriteEnable = VK_TRUE;
        configInfo.depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
        configInfo.depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
        configInfo.depthStencilInfo.minDepthBounds = 0.0f; // optional
        configInfo.depthStencilInfo.maxDepthBounds = 1.0f; // optional
        configInfo.depthStencilInfo.stencilTestEnable = VK_FALSE;
        configInfo.depthStencilInfo.front = {}; // optional
        configInfo.depthStencilInfo.back = {}; // optional

        return configInfo;
    }
} // alchemy