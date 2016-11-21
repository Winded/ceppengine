#pragma once

#include "object.h"
#include "gameobject.h"
#include "util/ref.h"
#include "components/rendering/camera.h"

namespace cepp {

class Scene : public Object
{
    public:
        Scene();

        GameObject *rootObject() const;

        Camera *mainCamera();

        GameObject *findGameObjectByName(const std::string &name);
        std::vector<GameObject*> findGameObjectsByName(const std::string &name);

        /**
         * Find the first component of given type in scene hierarchy.
         */
        Component *findComponent(const std::string &typeName);

    protected:
        void start();
        void update(float deltaTime);
        void destroy();

    private:
        void objectMatchIteration(GameObject *go);

        Ref<GameObject> mRootObject;

        Camera *mMainCamera;

        //std::vector<Camera*> mCameras;

        friend class Engine;
};

} // namespace cepp
