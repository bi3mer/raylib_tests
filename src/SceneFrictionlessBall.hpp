#ifndef SCENE_FRICTIONLESS_BALL_HPP
#define SCENE_FRICTIONLESS_BALL_HPP

#include <algorithm>
#include "raylib.h"
#include "raymath.h"
#include "IScene.hpp"

typedef struct Ball {
    Vector2 pos;
    Vector2 velocity;
    float radius;
} Ball;

class SceneFrictionlessBall : public IScene {
public: 
    SceneFrictionlessBall();
    ~SceneFrictionlessBall();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();

private:
    bool pause;
    Ball ball;

    const Vector2 G = { 0, 1 };
};
#endif