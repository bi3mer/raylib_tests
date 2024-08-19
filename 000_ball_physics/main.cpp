#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <cstdint>
#include <algorithm>

#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
#endif

typedef struct {
    Vector2 pos;
    Vector2 velocity;
    float radius;
} Ball;

const Vector2 G = { 0, 0.45 };

void step(void* voidBall) {
    Ball* ball = static_cast<Ball*>(voidBall);

    // constants for the frame
    const int W = GetScreenWidth();
    const int H = GetScreenHeight();
    const int min = std::min(H, W);

    // simulate 3 steps
    const float dt = GetFrameTime() / 3.0;
    const Vector2 gravity = Vector2Scale(G, dt);

    for (uint_fast8_t i = 0; i < 3; ++i) {
        ball->velocity = Vector2Add(ball->velocity, gravity);
        ball->pos = Vector2Add(ball->pos, Vector2Scale(ball->velocity, dt));

        if (ball->pos.x < 0.0) {
            ball->pos.x = 0.0;
            ball->velocity.x = -ball->velocity.x;
        } else if (ball->pos.x >= 1) {
            ball->pos.x = 1;
            ball->velocity.x = -ball->velocity.x;
        }

        if (ball->pos.y >= 1) {
            ball->pos.y = 1;
            ball->velocity.y = -ball->velocity.y;
        }
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(Vector2Multiply(ball->pos, {(float) W, (float) H}), ball->radius*min, RED);
    EndDrawing();
}

int main(void) {
    Ball ball = { 
        {
            0.5f, 
            0.5f
        }, 
        {
            0.25f + ((float)(rand()) / (float)(RAND_MAX)) / 5,
            0.1f + ((float)(rand()) / (float)(RAND_MAX)) /5
        }, 
        0.02f
    };

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(720, 480, "Frictionless Bouncing Ball");
    SetTargetFPS(60);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(step, static_cast<void*>(&ball), 60, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        step(static_cast<void*>(&ball));
    }
#endif


    CloseWindow();

    return 0;
}