//
// Created by lura on 5/17/23.
//

#ifndef ALCHEMINER_RENDERER_H
#define ALCHEMINER_RENDERER_H

namespace Engine {

    class renderer {
    public:
        static void initVulkan();

        static void update();

        static void cleanup();
    };

} // Engine

#endif //ALCHEMINER_RENDERER_H
