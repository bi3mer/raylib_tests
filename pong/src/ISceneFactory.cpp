#include "ISceneFactory.hpp"

ISceneFactory::ISceneFactory(const char* sceneName) : name(sceneName) { }
ISceneFactory::~ISceneFactory() { }

const char* ISceneFactory::getName() const {
    return this->name;
}