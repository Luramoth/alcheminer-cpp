//
// Created by lura on 5/18/23.
//

#ifndef ALCHEMINER_ALCHPIPELINE_H
#define ALCHEMINER_ALCHPIPELINE_H



#include <string>
#include <vector>

namespace alchemy {

    class AlchPipeline {
    public:
        AlchPipeline(const std::string vertFilePath, const std::string fragFilePath);

    private:
        static std::vector<char> readFile(const std::string filePath);

        void createGraphicsPipeline(const std::string vertFilePath, const std::string fragFilePath);
    };

} // alchemy

#endif //ALCHEMINER_ALCHPIPELINE_H
