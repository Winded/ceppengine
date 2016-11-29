#include "engine.h"

namespace cepp {

Engine *sInstance = 0;

Engine *Engine::instance()
{
    return sInstance;
}

Engine::Engine() : mRunning(false), mCachedRuntimeModule(0), mCachedInputModule(0), mCachedRenderModule(0), mNewScene(0)
{
    if(!sInstance)
        sInstance = this;
}

bool Engine::isRunning() const
{
    return mRunning;
}

AssetLoader *Engine::assetLoader()
{
    return &mAssetLoader;
}

const DefaultAssets *Engine::defaultAssets() const
{
    return &mDefaultAssets;
}

Scene *Engine::scene() const
{
    return mScene;
}

Module *Engine::getModule(const std::string &name) const
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

RuntimeModule *Engine::runtimeModule()
{
    if(mRunning && mCachedRuntimeModule) {
        return mCachedRuntimeModule;
    }
    else if(mRunning) {
        mCachedRuntimeModule = (RuntimeModule*)getModule("RuntimeModule");
        return mCachedRuntimeModule;
    }
    else {
        return (RuntimeModule*)getModule("RuntimeModule");
    }
}

InputModule *Engine::inputModule()
{
    if(mRunning && mCachedInputModule) {
        return mCachedInputModule;
    }
    else if(mRunning) {
        mCachedInputModule = (InputModule*)getModule("InputModule");
        return mCachedInputModule;
    }
    else {
        return (InputModule*)getModule("InputModule");
    }
}

RenderModule *Engine::renderModule()
{
    if(mRunning && mCachedRenderModule) {
        return mCachedRenderModule;
    }
    else if(mRunning) {
        mCachedRenderModule = (RenderModule*)getModule("RenderModule");
        return mCachedRenderModule;
    }
    else {
        return (RenderModule*)getModule("RenderModule");
    }
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
