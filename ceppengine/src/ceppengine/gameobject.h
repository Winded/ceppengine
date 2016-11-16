#pragma once

#include <string>
#include "object.h"
#include "util/ref.h"
#include "scene.h"
#include "math/vector3.h"

namespace cepp {

class Component;

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
        GameObject();
        GameObject(const std::string &name);

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

        Vector3 position() const;
        void setPosition(const Vector3 &position);
        Vector3 rotation() const;
        void setRotation(const Vector3 &rotation);
        Vector3 scale() const;
        void setScale(const Vector3 &scale);

        Vector3 localPosition() const;
        void setLocalPosition(const Vector3 &position);
        Vector3 localRotation() const;
        void setLocalRotation(const Vector3 &rotation);
        Vector3 localScale() const;
        void setLocalScale(const Vector3 &scale);

        Matrix4 localToWorldMatrix() const;
        Matrix4 worldToLocalMatrix() const;

        Vector3 forward() const;
        Vector3 right() const;
        Vector3 up() const;

    private:
        void invalidateTransformCache(bool position, bool rotation, bool scale, bool matrices);

        std::string mName;

        Ref<Scene> mScene;

        Ref<GameObject> mParent;

        std::vector<Ref<GameObject>> mChildren;
        std::vector<GameObject*> mIteratedChildren; // Different list for update loop iteration to allow removal and addition of children

        std::vector<Ref<Component>> mComponents;
        std::vector<Component*> mIteratedComponents;

        bool mChildrenChanged, mComponentsChanged;

        bool mActive, mStartCalled;

        Vector3 mLocalPosition, mLocalRotation, mLocalScale;

        // Caching is used to avoid calculating global vectors and matrices every time they are requested
        bool mCachePositionValid, mCacheRotationValid, mCacheScaleValid, mCacheLToWValid, mCacheWToLValid;
        Vector3 mCachePosition, mCacheRotation, mCacheScale;
        Matrix4 mCacheLToW, mCacheWToL;

        friend class Scene;
        friend class Component;
};

} // namespace cepp
