#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define DEBUG true

#include "app.hpp"
#include "scene_000_frictionless_ball.hpp"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "raylib Tests");
    SetTargetFPS(60);

    App app;
    while (!WindowShouldClose()) {
        app.update(GetFrameTime());
        
        BeginDrawing();
        app.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/** 
 * Ideal state machine usage:

    Scene* scene;
    SceneMenu menu;

    scene = &menu;

    while (!WindowShouldClose()) {
        Scene* new_scene = scene->change_scene();
        if (new_scene != nullptr) {
            scene->on_exit();
            new_scene->on_enter();
            scene = new_scene;
        }

        scene->update(GetFrameTime());

        BeginDrawing();
        scene->draw();
        EndDrawing();
    }

 */