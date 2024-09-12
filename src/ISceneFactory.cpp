#include "ISceneFactory.hpp"

ISceneFactory::ISceneFactory(char* sceneName) : name(sceneName) { }
ISceneFactory::~ISceneFactory() { }

char* ISceneFactory::getName() const {
    return this->name;
}