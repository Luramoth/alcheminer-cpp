//
// Created by lura on 5/17/23.
//

#ifndef ALCHEMINER_ENGINE_H
#define ALCHEMINER_ENGINE_H

namespace Engine {

    class engine {
    public:
        static void run();
    private:
        static void init();

        static void mainLoop();

        static void cleanup();
    };

} // Engine

#endif //ALCHEMINER_ENGINE_H
