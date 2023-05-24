#include <cstdlib>
#include <iostream>

#include <raylib.h>
#include <raymath.h>

int main() {
    std::cout << "Hello World!\n";

    int width = 800;
    int height = 450;
    InitWindow(width, height, "Alcheminer");

    Camera3D camera;
    camera.position = (Vector3){0, 10,10};
    camera.target = (Vector3){0, 0, 0,};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    Model cubeModel = LoadModelFromMesh(GenMeshCube(2, 2, 2));
    Vector3 cubePosition = {0, 0, 0};

    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera);

        // rotate cube
        cubeModel.transform = MatrixMultiply(cubeModel.transform, MatrixRotateY(DEG2RAD * 1));

        BeginDrawing();
        {
                ClearBackground(RAYWHITE);

                BeginMode3D(camera);
                {
                        DrawModel(cubeModel, cubePosition, 1, RED);
                }
                EndMode3D();
        }
        EndDrawing();
    }

    UnloadModel(cubeModel);
    CloseWindow();

    return EXIT_SUCCESS;
}
