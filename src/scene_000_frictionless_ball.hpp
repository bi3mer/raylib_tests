#ifndef __SCENE_000_FRICTIONLESS_BALL_HPP__
#define __SCENE_000_FRICTIONLESS_BALL_HPP__

#include "raylib.h"
#include "raymath.h"
#include "scene.hpp"

typedef struct Ball {
    Vector2 pos;
    Vector2 velocity;
    float radius;
} Ball;

class SceneFrictionlessBall : public Scene {
public: 
    SceneFrictionlessBall();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();
    virtual Scene* change_scene();

private:
    bool pause;
    Ball ball;

    const Vector2 G = { 0, 1 };
};
#endif