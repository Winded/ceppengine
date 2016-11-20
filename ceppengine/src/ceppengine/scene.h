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

        Camera *mainCamera() const;

    protected:
        void start();
        void update(float deltaTime);
        void destroy();

    private:
        Ref<GameObject> mRootObject;

        Camera *mMainCamera;

        //std::vector<Camera*> mCameras;

        friend class Engine;
};

} // namespace cepp
