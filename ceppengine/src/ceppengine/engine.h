#pragma once

#include "assets/assetloader.h"
#include "util/ref.h"
#include "modules/module.h"
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
        const AssetLoader *assetLoader() const;

        /**
         * Get currently loaded scene
         */
        Scene *scene() const;

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

        AssetLoader mAssetLoader;

        Ref<Scene> mScene;
        Scene *mNewScene;
};

} // namespace cepp

