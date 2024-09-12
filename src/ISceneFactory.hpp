#ifndef I_SCENE_FACTORY_HPP
#define I_SCENE_FACTORY_HPP

#include "scene.hpp"

class ISceneFactory {
public:
    ISceneFactory(char *);
    virtual ~ISceneFactory();

    char* getName() const;
    virtual IScene* constructScene() const = 0;
private:
    char* name;
};

#endif