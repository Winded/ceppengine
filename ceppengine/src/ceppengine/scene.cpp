#include "scene.h"
#include "gameobject.h"
#include <functional>

namespace cepp {

Scene::Scene() : mMainCamera(0)
{
    mRootObject = new GameObject("Root");
    mRootObject->mScene = this;
}

GameObject *Scene::rootObject() const
{
    return mRootObject;
}

Camera *Scene::mainCamera()
{
    if(!mMainCamera)
        mMainCamera = (Camera*)findComponent("Camera");
    return mMainCamera;
}

GameObject *Scene::findGameObjectByName(const std::string &name)
{
    std::vector<GameObject*> objs = findGameObjectsByName(name);
    if(objs.size() > 0)
        return objs.at(0);
    else
        return 0;
}

std::vector<GameObject *> Scene::findGameObjectsByName(const std::string &name)
{
    return mRootObject->recursiveFindGameObjects(name);
}

Component *Scene::findComponent(const std::string &typeName)
{
    return mRootObject->recursiveFindComponent(typeName);
}

void Scene::start()
{
    mRootObject->start();
}

void Scene::update(float deltaTime)
{
    mRootObject->update(deltaTime);
}

void Scene::destroy()
{
    mRootObject = 0;
}

void Scene::objectMatchIteration(GameObject *go)
{

}

} // namespace cepp
