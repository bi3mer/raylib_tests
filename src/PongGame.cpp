#include "PongGame.hpp"
#include "stdio.h"

PongGame::PongGame() { 
    aiScore = 0;
    playerScore = 0;
}

PongGame::~PongGame() { }

void PongGame::on_enter() {
    ball = { .x = 0.5f, .y = 0.5f };
    ballVelocity = { .x = -0.3f, .y = 0.0f};
    
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

    // update player paddle position, and do not let the paddle go past the 
    // screen's borders
    const float moveModifier = paddleModifier * dt;
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && playerPaddle.y - moveModifier >= 0) {
        playerPaddle.y -= moveModifier;
    }

    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && playerPaddle.y + playerPaddle.height + moveModifier <= 1) {
        playerPaddle.y += moveModifier;
    }

    // update ai paddle position based on the ball's next position
    const float ballNextHeight = ball.y + ballVelocity.y * dt;
    if (ballNextHeight > aiPaddle.y + aiPaddle.height) {
        aiPaddle.y += moveModifier;
    } else if (ballNextHeight < aiPaddle.y) {
        aiPaddle.y -= moveModifier;
    }

    // Ball is rendered based on width, so it's easier to use world position
    // for collisions. Since the results are used in the draw call, they are
    // kept local to the class to not calculate the same thing twice.
    const float W = GetScreenWidth();
    const float H = GetScreenHeight();
    worldPlayerPaddle = {
        .x = playerPaddle.x * W + playerPaddle.width - 0.01f, // see comment at the end of the function 
        .y = playerPaddle.y * H, 
        .width = 0.01f,
        .height = playerPaddle.height * H
    };

    worldAIPaddle = {
        .x = aiPaddle.x * W, 
        .y = aiPaddle.y * H, 
        .width = 0.1f,
        .height = aiPaddle.height * H
    };

    // update ball position in small steps
    const float diffDT = dt / 5.0f;
    for (std::size_t i = 0; i < 5; ++i) {
        ball.x += ballVelocity.x * diffDT;
        ball.y += ballVelocity.y * diffDT;

        const float br = ballRadius * fmin(W, H);
        const Vector2 b = { .x = ball.x * W, .y = ball.y * H};

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
        } else if (ball.y >= 1.0) { // collision with bottom wall
            ball.y = 0.99f;
            ballVelocity.y *= -speedUp; 
        } else if (ball.y <= 0.0) {   
            ball.y = 0.01f;
            ballVelocity.y *= -speedUp; 
        } else if (CheckCollisionCircleRec(b, br, worldPlayerPaddle)) { 
            // ---- collision with player paddle ----
            // Move away from paddle to prevent duplicate collisions
            ball.x += 0.01f;          
            
            const float anglePercent = (ball.y - playerPaddle.y) / playerPaddle.height;
            const float angle = -Lerp(-maxBounceAngle, maxBounceAngle, anglePercent);
            const float ballSpeed = Vector2Length(ballVelocity);

            ballVelocity.x = cos(angle) * ballSpeed * speedUp;
            ballVelocity.y = -sin(angle) * ballSpeed;
        } else if (CheckCollisionCircleRec(b, br, worldAIPaddle)) {
            // ---- collision with AI paddle ----
            // code logic is exactly the same as the player paddle above
            ball.x -= 0.01f;
            
            const float anglePercent = (ball.y - aiPaddle.y) / aiPaddle.height;
            const float angle = -Lerp(-maxBounceAngle, maxBounceAngle, anglePercent);
            const float ballSpeed = Vector2Length(ballVelocity);

            ballVelocity.x = -cos(angle) * ballSpeed * speedUp;
            ballVelocity.y = -sin(angle) * ballSpeed;
        }
    }

    // Wanted collision with AI paddle to be one sided:
    //
    // XXXX      ---X
    // XXXX  to  ---X
    // XXXX      ---X
    //
    // Now the correct values are needed for rendering when draw() is called
    worldPlayerPaddle.x = playerPaddle.x * W;
    worldPlayerPaddle.width = playerPaddle.width * W; 

    worldAIPaddle.width = aiPaddle.width * W;
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
    DrawRectangleRounded(worldPlayerPaddle, paddleRounded, 1, BLACK);
    DrawRectangleRounded(worldAIPaddle, paddleRounded, 1, BLACK);

    // render ball
    DrawCircle(ball.x * W, ball.y * H, ballRadius*fmin(W, H), BLACK);
}