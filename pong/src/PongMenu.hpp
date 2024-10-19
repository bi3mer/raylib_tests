#ifndef PONG_MENU_HPP
#define PONG_MENU_HPP

#include "raylib.h"
#include "raymath.h"

#include "IScene.hpp"

class PongMenu : public IScene {
public: 
    PongMenu();
    ~PongMenu();

    virtual void on_enter();
    virtual void on_exit();
    virtual void update(float dt);
    virtual void draw();

private:
    const float titleSize = 32;
    const float instructionSize = 20;
    const char* title = "Pong";
    const char* instructions = "Press SPACE to start";
    
    bool showInstructions;
    float instructionsBlinkTime;
    Vector2 titleDimensions;
    Vector2 instructionDimensions;
};
#endif
