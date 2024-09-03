#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#ifdef DEBUG
#include <cassert>
#endif

#include <stdexcept>
#include <vector>

// Scene is a node in a graph with outgoing edges.
class Scene {
public:
    virtual void on_enter() = 0;
    virtual void on_exit() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual Scene* change_scene() = 0;

    void add_dst_scene(Scene* scene) {
        #ifdef DEBUG
        printf("Checking scene...\n");
        for (auto* s : this->dst_scenes) {
            assert(s != scene);
        }
        #endif

        dst_scenes.push_back(scene);
    }
protected:
    std::vector<Scene*> dst_scenes;
};
#endif