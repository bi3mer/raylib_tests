#ifndef I_SCENE_FACTORY_HPP
#define I_SCENE_FACTORY_HPP

#include "IScene.hpp"

class ISceneFactory {
public:
    ISceneFactory(const char *);
    virtual ~ISceneFactory();

    const char* getName() const;
    virtual IScene* constructScene() const = 0;
private:
    const char* name;
};

#endif