#include "scene.h"
#include "gameobject.h"

namespace cepp {

Scene::Scene() : mMainCamera(0)
{
    mRootObject = new GameObject("Root");
    mRootObject->mScene = this;
}

Camera *Scene::mainCamera() const
{
    // TODO find main camera
    return mMainCamera;
}

void Scene::start()
{

}

void Scene::update(float deltaTime)
{

}

void Scene::destroy()
{

}

} // namespace cepp
