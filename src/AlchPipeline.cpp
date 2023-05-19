//
// Created by lura on 5/18/23.
//

#include "AlchPipeline.h"
#include <fstream>
#include <iostream>

namespace alchemy {
    AlchPipeline::AlchPipeline(const std::string vertFilePath, const std::string fragFilePath) {
        createGraphicsPipeline(vertFilePath, fragFilePath);
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

    void AlchPipeline::createGraphicsPipeline(const std::string vertFilePath, const std::string fragFilePath) {

        // read out shader code
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "Vertex shader file size: " << vertCode.size() << '\n';
        std::cout << "Fragment shader file size: " << fragCode.size() << '\n';
    }
} // alchemy