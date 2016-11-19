#pragma once

#include "object.h"
#include "gameobject.h"
#include "util/ref.h"

namespace cepp {

class Scene : public Object
{
    public:
        Scene();

    protected:
        void start();
        void update(float deltaTime);
        void destroy();

    private:
        Ref<GameObject> mRootObject;

        //std::vector<Camera*> mCameras;

        friend class Engine;
};

} // namespace cepp
