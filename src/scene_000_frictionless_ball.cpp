#include "scene_000_frictionless_ball.hpp"

SceneFrictionlessBall::SceneFrictionlessBall() {
    this->pause = false;
    this->ball = {
        .pos = { 0.5f, 0.5f},
        .velocity = {
            0.25f + ((float)(rand()) / (float)(RAND_MAX)) / 5,
            0.1f + ((float)(rand()) / (float)(RAND_MAX)) / 5
        },
        .radius = 0.02f
    };
}

void SceneFrictionlessBall::on_enter() {
    // do nothing
}

void SceneFrictionlessBall::on_exit() {
    // do nothing
}

void SceneFrictionlessBall::update(float dt) {
    if (IsKeyPressed(KEY_SPACE)) {
        this->pause = !this->pause;
    }

    if (!this->pause) {
        // simulate 3 steps
        const float dt = GetFrameTime() / 3.0;
        const Vector2 gravity = Vector2Scale(G, dt);

        for (uint_fast8_t i = 0; i < 3; ++i) {
            ball.velocity = Vector2Add(ball.velocity, gravity);
            ball.pos = Vector2Add(ball.pos, Vector2Scale(ball.velocity, dt));

            if (ball.pos.x < 0.0) {
                ball.pos.x = 0.0;
                ball.velocity.x = -ball.velocity.x;
            } else if (ball.pos.x >= 1) {
                ball.pos.x = 1;
                ball.velocity.x = -ball.velocity.x;
            }

            if (ball.pos.y >= 1) {
                ball.pos.y = 1;
                ball.velocity.y = -ball.velocity.y;
            }
        }  
    } 
}

void SceneFrictionlessBall::draw() {
    const int W = GetScreenWidth();
    const int H = GetScreenHeight();
    const int min = std::min(H, W);

    ClearBackground(RAYWHITE);
    DrawCircleV(Vector2Multiply(ball.pos, {(float) W, (float) H}), ball.radius*min, RED);

    DrawText("Press space to pause and unpause.", 10, 10, 20, GRAY);

    if (this->pause) {
        Vector2 dimension = MeasureTextEx(GetFontDefault(), "PAUSED", 50, 1);
        DrawText("PAUSED", (W - dimension.x) / 2, (H- dimension.y) / 2, 50, GRAY);
    }
}


Scene* SceneFrictionlessBall::change_scene() {
    return nullptr;
}