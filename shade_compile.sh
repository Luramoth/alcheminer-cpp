mkdir "./cmake-build-debug/shaders/"

glslc ./src/shaders/simple.vert -o ./cmake-build-debug/shaders/simple.vert.spv
glslc ./src/shaders/simple.frag -o ./cmake-build-debug/shaders/simple.frag.spv
