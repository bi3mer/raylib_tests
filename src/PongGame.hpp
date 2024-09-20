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
    Vector2 ball;
    Vector2 ballVelocity;
    Vector2 playerPaddle;
    Vector2 aiPaddle;
};
#endif