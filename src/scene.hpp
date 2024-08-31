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
    void on_enter() {
        throw std::logic_error("`on_enter` not implemented");
    }

    void on_exit() {
        throw std::logic_error("`on_exit` not implemented");
    }

    void update(float dt) {
        throw std::logic_error("`update` not implemented");
    }

    void physics_update(float dt) {
        throw std::logic_error("`physics_update` not implemented");
    }

    void draw() {
        throw std::logic_error("`draw` not implemented");
    }

    Scene* change_scene() {
        throw std::logic_error("`change_scene` not implemented");
    }

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