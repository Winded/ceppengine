#include "engine.h"

namespace cepp {

Engine *sInstance = 0;

Engine *Engine::instance()
{
    return sInstance;
}

Engine::Engine() : mRunning(false)
{
    if(!sInstance)
        sInstance = this;
}

bool Engine::isRunning() const
{
    return mRunning;
}

const AssetLoader *Engine::assetLoader() const
{
    return &mAssetLoader;
}

Scene *Engine::scene() const
{
    return mScene;
}

Module *Engine::getModule(std::string name) const
{
    for(auto it = mModules.begin(); it != mModules.end(); ++it) {
        if((*it)->name() == name)
            return (*it);
    }
}

void Engine::addModule(Module *module)
{
    mModules.push_back(module);
}

void Engine::loadScene(Scene *scene)
{
    if(!mRunning) {
        mScene = scene;
        return;
    }

    mNewScene = scene;
}

void Engine::start()
{
    assert(!mRunning);
    assert(mScene);

    mRunning = true;

    for(auto it = mModules.begin(); it != mModules.end(); ++it)
        (*it)->initialize();

    mScene->start();
}

void Engine::update(float deltaTime)
{
    assert(mRunning);

    // Load new scene
    if(mNewScene) {
        mScene->destroy();
        mScene = mNewScene;
        mNewScene = 0;
        mScene->start();
    }

    // Call preUpdate on modules (used to process input, for example)
    for(auto it = mModules.begin(); it != mModules.end(); ++it)
        (*it)->preUpdate(deltaTime);

    // Update scene
    mScene->update(deltaTime);

    // Call postUpdate on modules (used for rendering, for example)
    for(auto it = mModules.begin(); it != mModules.end(); ++it)
        (*it)->postUpdate(deltaTime);

    // Engine was stopped during updates; unload all engine assets
    if(!mRunning) {
        mScene = 0;
        mAssetLoader.unloadAssets(); // Unload assets from memory in a controlled manner
        mModules.clear();
    }
}

void Engine::stop()
{
    mRunning = false;
}

} // namespace cepp
