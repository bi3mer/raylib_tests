#include "raylib.h"
#include "raymath.h"
#include <cstdint>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    Vector2 pos;
    Vector2 velocity;
    float radius;
} Ball;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Frictionless Bouncing Ball");
    SetTargetFPS(60);

    const Vector2 G = { 0, 200.0 }; // coordinate swap

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

    while (!WindowShouldClose()) {
        const int W = GetScreenWidth();
        const int H = GetScreenHeight();

        // simulate 3 steps
        const float dt = GetFrameTime() / 3.0;
        const Vector2 gravity = Vector2Scale(G, dt);

        for (uint_fast8_t i = 0; i < 3; ++i) {
            ball.velocity = Vector2Add(ball.velocity, gravity);
            ball.pos = Vector2Add(ball.pos, Vector2Scale(ball.velocity, dt));

            if (ball.pos.x < 0.0) {
                ball.pos.x = 0.0;
                ball.velocity.x = -ball.velocity.x;
            } else if (ball.pos.x >= W) {
                ball.pos.x = W;
                ball.velocity.x = -ball.velocity.x;
            }

            if (ball.pos.y >= H) {
                ball.pos.y = H;
                ball.velocity.y = -ball.velocity.y;
            }
        }
        

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(ball.pos, ball.radius, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}