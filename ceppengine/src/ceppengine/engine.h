#pragma once

#include "assets/assetloader.h"
#include "assets/default.h"
#include "util/ref.h"
#include "modules/module.h"
#include "modules/runtimemodule.h"
#include "modules/inputmodule.h"
#include "modules/rendermodule.h"
#include "scene.h"
#include <vector>

namespace cepp {

/**
 * Singleton object that maintains everything the engine needs to operate; modules, assets and scenes.
 */
class Engine
{
    public:
        static Engine *instance();

        Engine();

        /**
         * Returns whether the engine is currently running or not
         */
        bool isRunning() const;

        /**
         * Get asset loader.
         */
        AssetLoader *assetLoader();
        /**
         * Get default assets
         */
        const DefaultAssets *defaultAssets() const;

        /**
         * Get currently loaded scene
         */
        Scene *scene() const;

        Module *getModule(const std::string &name) const;
        void addModule(Module *module);

        // Function shortcuts for generic module types
        RuntimeModule *runtimeModule();
        InputModule *inputModule();
        RenderModule *renderModule();

        /**
         * Load a scene into the engine. This needs to be called before starting the engine.
         * The engine cannot run without a scene.
         */
        void loadScene(Scene *scene);

        void start();
        void update(float deltaTime);
        void stop();

    private:
        bool mRunning;

        std::vector<Ref<Module>> mModules;

        RuntimeModule *mCachedRuntimeModule;
        InputModule *mCachedInputModule;
        RenderModule *mCachedRenderModule;

        AssetLoader mAssetLoader;
        DefaultAssets mDefaultAssets;

        Ref<Scene> mScene;
        Scene *mNewScene;
};

} // namespace cepp

