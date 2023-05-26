#include <cstdlib>
#include <iostream>

#include <raylib.h>
#include <raymath.h>

#include "rlFPCamera.h"

int main() {
    std::cout << "Hello World!\n";

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    int width = 800;
    int height = 450;
    InitWindow(width, height, "Alcheminer");

    rlFPCamera cam;
    rlFPCameraInit(&cam, 75, (Vector3){0, 0, -10});
    cam.MoveSpeed.z = 20;
    cam.MoveSpeed.x = 15;

    cam.FarPlane = 5000;

    cam.AllowFlight = true;

    Model cubeModel = LoadModelFromMesh(GenMeshCube(2, 2, 2));
    Vector3 cubePosition = {0, 0, 0};

    while (!WindowShouldClose()) {
        rlFPCameraUpdate(&cam);

        // rotate cube
        cubeModel.transform = MatrixMultiply(cubeModel.transform, MatrixRotateY(DEG2RAD * 100 * GetFrameTime()));

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            rlFPCameraBeginMode3D(&cam);
            {
                DrawModel(cubeModel, cubePosition, 1, RED);
            }
            rlFPCameraEndMode3D();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    UnloadModel(cubeModel);
    CloseWindow();

    return EXIT_SUCCESS;
}
