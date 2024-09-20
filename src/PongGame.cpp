#include "PongGame.hpp"
#include "stdio.h"
/**
 * [ ] Ball collision with paddles
 */

PongGame::PongGame() { 
    aiScore = 0;
    playerScore = 0;
}

PongGame::~PongGame() { }

void PongGame::on_enter() {
    ball = { .x = 0.5f, .y = 0.5f };
    ballVelocity = { .x = -0.2f, .y = 0.0f};
    
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

    aiScore = 0;
    playerScore = 0;
}

void PongGame::update(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        changeScene = true;
    }

    // update player paddle
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        playerPaddle.y -= paddleModifier * dt;
    }

    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        playerPaddle.y += paddleModifier * dt;
    }

    // update ai paddle
    const float ballNextHeight = ball.y + ballVelocity.y*dt;
    if (ballNextHeight > aiPaddle.y + aiPaddle.height) {
        aiPaddle.y += paddleModifier * dt;
    } else if (ballNextHeight < aiPaddle.y) {
        aiPaddle.y -= paddleModifier * dt;
    }

    // update ball position in small steps
    const float diffDT = dt / 5.0f;
    for (std::size_t i = 0; i < 5; ++i) {
        ball.x += ballVelocity.x * diffDT;
        ball.y += ballVelocity.y * diffDT;

        if (ball.x >= 1.0) {
            ++playerScore;
            
            // reset the ball and its velocity
            ball.x = 0.5f;
            ball.y = 0.5f;
            ballVelocity.x = 0.2f; 
            ballVelocity.y = 0.0f;
        } else if (ball.x <= 0) {
            ++aiScore;
            
            // reset the ball and its velocity
            ball.x = 0.5f;
            ball.y = 0.5f;
            ballVelocity.x = -0.2f; 
            ballVelocity.y = 0.0f;
        } else if (ball.y >= 1.0) {   // collision with bottom wall
            ball.y = 0.99f;           // reset ball position
            ballVelocity.y *= -1.01f; // speed ball up
        } else if (ball.y <= 0.0) {   
            ball.y = 0.01f;
            ballVelocity.y *= -1.01f; 
        } else if (CheckCollisionCircleRec(ball, ballRadius, playerPaddle)) { 
            // collision with player paddle
            printf("Collision with player paddle!\n");
            ballVelocity.x *= -1.01f;
        } else if (CheckCollisionCircleRec(ball, ballRadius, aiPaddle)) {
            // collision with ai paddle
            printf("Collision with ai paddle!\n");
            ballVelocity.x *= -1.01f;
        }
        
        // top-bottom wall collisions
        // side collision behavior (score + reset ball)
    }
}

void PongGame::draw() {
    ClearBackground(RAYWHITE);
    const float W = GetScreenWidth();
    const float H = GetScreenHeight();

    // draw ai and player score
    char buffer[5]; // no way someone goes past 5 digits
    snprintf(buffer, sizeof(buffer), "%i", playerScore);
    DrawText(buffer, W * 0.25f, H * 0.1f, scoreTextSize, GRAY);

    snprintf(buffer, sizeof(buffer), "%i", aiScore);
    DrawText(buffer, W * 0.75f, H * 0.1f, scoreTextSize, GRAY);

    // draw half-line with blinking line
    const float startY = 0.05f;
    const float lineHeight = 0.048f;
    const float halfX = W / 2.0f;
    for (std::size_t i = 0; i < 11; ++i) {
        const float y = startY + i * 2 * lineHeight;
        DrawLineEx(
            {halfX, y * H},
            {halfX, (y + lineHeight) * H}, 
            4,
            GRAY
        );
    }

    // render player paddle
    const Rectangle worldPlayerPaddle = {
        .x = playerPaddle.x * W, 
        .y = playerPaddle.y * H, 
        .width = playerPaddle.width * W, 
        .height = playerPaddle.height * H
    };

    DrawRectangleRounded(worldPlayerPaddle, paddleRounded, 1, BLACK);

    // render ai paddle
    const Rectangle worldAIPaddle = {
        .x = aiPaddle.x * W, 
        .y = aiPaddle.y * H, 
        .width = aiPaddle.width * W, 
        .height = aiPaddle.height * H
    };

    DrawRectangleRounded(worldAIPaddle, paddleRounded, 1, BLACK);

    // render ball
    DrawCircle(ball.x * W, ball.y * H, W*ballRadius, BLACK);
}