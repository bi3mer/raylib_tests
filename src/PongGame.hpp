#ifndef PONG_GAME_HPP
#define PONG_GAME_HPP

#include "raylib.h"
#include "raymath.h"

#include "IScene.hpp"

class PongGame : public IScene {
public: 
    PongGame();
    ~PongGame();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();

private:
    const float scoreTextSize = 30;
    const float paddleModifier = 0.5f;
    const float paddleRounded = 0.5f;
    const float ballRadius = 0.01f;

    int playerScore;
    int aiScore;

    Vector2 ball;
    Vector2 ballVelocity;
    Rectangle playerPaddle;
    Rectangle aiPaddle;

    Rectangle worldPlayerPaddle;
    Rectangle worldAIPaddle;
};
#endif