#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <cstdint>

#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    Vector2 pos;
    Vector2 velocity;
    float radius;
} Ball;

const Vector2 G = { 0, 200.0 }; // coordinate swap



void step(void* voidBall) {
    Ball* ball = static_cast<Ball*>(voidBall);

    // constants for the frame
    const int W = GetScreenWidth();
    const int H = GetScreenHeight();

    // simulate 3 steps
    const float dt = GetFrameTime() / 3.0;
    const Vector2 gravity = Vector2Scale(G, dt);

    for (uint_fast8_t i = 0; i < 3; ++i) {
        ball->velocity = Vector2Add(ball->velocity, gravity);
        ball->pos = Vector2Add(ball->pos, Vector2Scale(ball->velocity, dt));

        if (ball->pos.x < 0.0) {
            ball->pos.x = 0.0;
            ball->velocity.x = -ball->velocity.x;
        } else if (ball->pos.x >= W) {
            ball->pos.x = W;
            ball->velocity.x = -ball->velocity.x;
        }

        if (ball->pos.y >= H) {
            ball->pos.y = H;
            ball->velocity.y = -ball->velocity.y;
        }
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(ball->pos, ball->radius, RED);
    EndDrawing();
}

int main(void) {
    Ball ball = { 
        {
            (float) GetScreenWidth() / 2, 
            (float) GetScreenHeight() / 2
        }, 
        {
            20.0f + ((float)(rand()) / (float)(RAND_MAX)) * 50.0f,
            30.0f + ((float)(rand()) / (float)(RAND_MAX)) * 50.0f
        }, 
        10 
    };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Frictionless Bouncing Ball");
    SetTargetFPS(60);

#ifdef EMSCRIPTEN
    printf("Web version\n");
    emscripten_set_main_loop_arg(step, static_cast<void*>(&ball), 60, 1);
#else
    printf("Not web\n");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        step(static_cast<void*>(&ball));
    }
#endif


    CloseWindow();

    return 0;
}