#pragma once

#include <string>
#include "object.h"
#include "math/vector3.h"
#include "math/matrix4.h"
#include "util/ref.h"
#include "components/component.h"

namespace cepp {

class Scene;

/**
 * Game objects are objects in the game scene that have a 3-dimensional position, rotation and scale.
 * Game objects live in a hierarchy, where one game object acts as the scene root and all other objects
 * are its children.
 * Components are attached to gameobjects to give them functionality. On their own, they only have a parent
 * and a position in the world.
 */
class GameObject : public Object
{
    public:
        typedef void (*Callback)(GameObject*);

        GameObject();
        GameObject(const std::string &name);
        ~GameObject();

        std::string name() const;
        void setName(const std::string &name);

        Scene *scene() const;

        GameObject *parent() const;
        void setParent(GameObject *parent, bool maintainLocalTransform = false);

        const std::vector<Ref<GameObject>> &children() const;

        const std::vector<Ref<Component>> &components() const;

        bool isActive() const;
        void setActive(bool active);

        bool isActiveInHierarchy() const;

        bool isDestroyed() const;
        /**
         * Destroy the GameObject. Note that this does not automatically delete the object from memory;
         * it first destroys all children and components, and then removes this game object from it's parent, removing
         * it from the scene hierarchy. If no other object references this object, it is deleted from memory.
         */
        void destroy();

        Vector3 position();
        void setPosition(const Vector3 &position);
        Vector3 rotation();
        void setRotation(const Vector3 &rotation);
        Vector3 scale();
        void setScale(const Vector3 &scale);

        Vector3 localPosition() const;
        void setLocalPosition(const Vector3 &position);
        Vector3 localRotation() const;
        void setLocalRotation(const Vector3 &rotation);
        Vector3 localScale() const;
        void setLocalScale(const Vector3 &scale);

        Matrix4 localToWorldMatrix();
        Matrix4 worldToLocalMatrix();

        Vector3 forward();
        Vector3 right();
        Vector3 up();

        /**
         * Get component attached to this game object with specified type name
         */
        Component *getComponent(const std::string &name) const;
        /**
         * Add a new component to this game object
         */
        Component *addComponent(Component *component);
        void removeComponent(Component *component);

    private:
        std::vector<GameObject*> recursiveFindGameObjects(const std::string &name);
        Component *recursiveFindComponent(const std::string &typeName);

        void invalidateTransformCache(bool position, bool rotation, bool scale, bool matrices);

        void start();
        void update(float deltaTime);

        std::string mName;

        Scene *mScene;

        GameObject *mParent;

        std::vector<Ref<GameObject>> mChildren;
        std::vector<Ref<GameObject>> mIteratedChildren; // Different list for update loop iteration to allow removal and addition of children

        std::vector<Ref<Component>> mComponents;
        std::vector<Ref<Component>> mIteratedComponents;

        bool mChildrenChanged, mComponentsChanged;

        bool mActive, mStartCalled, mDestroyed;

        Vector3 mLocalPosition, mLocalRotation, mLocalScale;

        // Caching is used to avoid calculating global vectors and matrices every time they are requested
        bool mCachePositionValid, mCacheRotationValid, mCacheScaleValid, mCacheLToWValid, mCacheWToLValid;
        Vector3 mCachePosition, mCacheRotation, mCacheScale;
        Matrix4 mCacheLToW, mCacheWToL;

        friend class Scene;
        friend class Component;
};

} // namespace cepp
