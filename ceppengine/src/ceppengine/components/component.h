#pragma once

#include "../object.h"

namespace cepp {

class GameObject;

/**
 * Components can be added to gameobjects to implement functionality, for example, to render a 3D shape for an object.
 */
class Component : public Object
{
    public:
        Component();
        ~Component();

        /**
         * Each component type should have their own type name. This is used to identify components of different types.
         */
        virtual std::string typeName() const = 0;

        /**
         * Get the game object this component is attached to
         */
        GameObject *gameObject() const;

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        GameObject *mGameObject;

        bool mStartCalled;

        friend class GameObject;
};

} // namespace cepp
