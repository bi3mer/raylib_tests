#ifndef N_BODY_HPP
#define N_BODY_HPP

#include "raylib.h"
#include "raymath.h"

#include "IScene.hpp"

class NBody : public IScene {
public: 
    NBody();
    ~NBody();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();

private:
};
#endif