#include "PongGame.hpp"

/**
 * [X] Render player paddle
 * [X] Render ai paddle
 * [ ] Render ball
 * [X] Player paddle movement
 * [ ] AI paddle movement
 * [ ] Ball movement
 * [ ] Ball collision with paddles
 * [ ] Ball collision with top or bottom wall
 * [ ] Ball collision with side walls
 * [ ] Score board
 * [ ] Dotted line down the middle
 */

PongGame::PongGame() { }

PongGame::~PongGame() { }

void PongGame::on_enter() {
    ball = { .x = 0.5f, .y = 0.5f };
    ballVelocity = { .x = 0.1f, .y = 0.0f};
    
    playerPaddle = { 
        .x = 0.05f, 
        .y = 0.5f, 
        .width = 0.01f, 
        .height = 0.12f
    };

    aiPaddle = {
        .x = 0.95f, 
        .y = 0.5f, 
        .width = 0.01f, 
        .height = 0.12f
    };
}

void PongGame::on_exit() {
    changeScene = false;
}

void PongGame::update(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        changeScene = true;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        playerPaddle.y -= paddleModifier;
    }

    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        playerPaddle.y += paddleModifier;
    }
}

void PongGame::draw() {
    ClearBackground(RAYWHITE);
    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    // render player paddle
    const Rectangle worldPlayerPaddle = {
        .x = playerPaddle.x * W, 
        .y = playerPaddle.y * H, 
        .width = playerPaddle.width * W, 
        .height = playerPaddle.height * H
    };

    DrawRectangleRounded(worldPlayerPaddle, 0.15f, 1, BLACK);

    // render ai paddle
    const Rectangle worldAIPaddle = {
        .x = aiPaddle.x * W, 
        .y = aiPaddle.y * H, 
        .width = aiPaddle.width * W, 
        .height = aiPaddle.height * H
    };

    DrawRectangleRounded(worldAIPaddle, 0.15f, 1, BLACK);

    // render ball paddle
    // const Rectangle worldPlayerPaddle = {
    //     .x = playerPaddle.x * W, 
    //     .y = playerPaddle.y * H, 
    //     .width = playerPaddle.width * W, 
    //     .height = playerPaddle.height * H
    // };

    // DrawRectangleRounded(worldPlayerPaddle, 0.15f, 1, BLACK);
    
}