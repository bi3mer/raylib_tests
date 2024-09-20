#ifndef SCENE_FACTORY_HPP
#define SCENE_FACTORY_HPP

#include "ISceneFactory.hpp"

template <class T>
class SceneFactory : public ISceneFactory {
public:
    SceneFactory(const char* name) : ISceneFactory(name) { }
    ~SceneFactory() { }

    IScene* constructScene() const {
        return new T();
    }
};

#endif