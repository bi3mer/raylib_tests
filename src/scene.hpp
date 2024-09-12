#ifndef __SCENE_HPP__
#define __SCENE_HPP__

class IScene {
public:
    bool changeScene = false;

    virtual ~IScene() = default;
    virtual void on_enter() = 0;
    virtual void on_exit() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};
#endif