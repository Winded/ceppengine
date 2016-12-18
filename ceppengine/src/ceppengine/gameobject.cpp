#include "gameobject.h"
#include "math/matrix4.h"
#include <algorithm>

namespace cepp {

GameObject::GameObject() : GameObject("GameObject")
{

}

GameObject::GameObject(const std::string &name)
{
    mName = name;
    mScene = 0;
    mParent = 0;
    mActive = true;
    mStartCalled = false;
    mDestroyed = false;
    mChildrenChanged = true;
    mComponentsChanged = true;
    mLocalScale = Vector3::one;
    mCachePositionValid = false;
    mCacheRotationValid = false;
    mCacheScaleValid = false;
    mCacheLToWValid = false;
    mCacheWToLValid = false;
}

GameObject::~GameObject()
{

}

std::string GameObject::name() const
{
    return mName;
}

void GameObject::setName(const std::string &name)
{
    mName = name;
}

Scene *GameObject::scene() const
{
    return mScene;
}

GameObject *GameObject::parent() const
{
    return mParent;
}

void GameObject::setParent(GameObject *parent, bool maintainLocalTransform)
{
    if(!maintainLocalTransform) {
        if(parent) {
            Matrix4 wToL = parent->worldToLocalMatrix();
            Matrix4 pMatrix = wToL * position().toPositionMatrix();
            Matrix4 rMatrix = wToL * rotation().toRotationMatrix();
            Matrix4 sMatrix = wToL * scale().toScaleMatrix();
            mLocalPosition = Vector3::fromPositionMatrix(pMatrix);
            mLocalRotation = Vector3::fromRotationMatrix(rMatrix);
            mLocalScale = Vector3::fromScaleMatrix(sMatrix);
        }
        else {
            mLocalPosition = position();
            mLocalRotation = rotation();
            mLocalScale = scale();
        }
    }
    invalidateTransformCache(true, true, true, true);

    if(mParent) {
        auto it = std::find_if(mParent->mChildren.begin(), mParent->mChildren.end(), [this](const Ref<GameObject> &go) {
            return go == this;
        });
        mParent->mChildren.erase(it);
        mParent->mChildrenChanged = true;
    }

    if(!parent) {
        mParent = 0;
        return;
    }

    mScene = parent->scene();
    mParent = parent;
    mParent->mChildren.push_back(this);
    mParent->mChildrenChanged = true;
}

const std::vector<Ref<GameObject> > &GameObject::children() const
{
    return mChildren;
}

const std::vector<Ref<Component> > &GameObject::components() const
{
    return mComponents;
}

bool GameObject::isActive() const
{
    return mActive;
}

void GameObject::setActive(bool active)
{
    mActive = active;
}

bool GameObject::isActiveInHierarchy() const
{
    if(!mActive)
        return false;
    if(mParent)
        return mParent->isActiveInHierarchy();
    else
        return true;
}

bool GameObject::isDestroyed() const
{
    return mDestroyed;
}

void GameObject::destroy()
{
    for(auto it = mIteratedChildren.begin(); it != mIteratedChildren.end(); ++it) {
        (*it)->destroy();
    }
    for(auto it = mIteratedComponents.begin(); it != mIteratedComponents.end(); ++it) {
        (*it)->destroy();
    }
    if(mParent)
        setParent(0, true);
    mDestroyed = true;
}

Vector3 GameObject::position()
{
    if(mCachePositionValid)
        return mCachePosition;

    if(mParent) {
        Matrix4 lToW = mParent->localToWorldMatrix();
        mCachePosition = Vector3::fromPositionMatrix(lToW * mLocalPosition.toPositionMatrix());
    }
    else {
        mCachePosition = mLocalPosition;
    }

    mCachePositionValid = true;
    return mCachePosition;
}

void GameObject::setPosition(const Vector3 &position)
{
    if(mParent) {
        Matrix4 wToL = mParent->worldToLocalMatrix();
        setLocalPosition(Vector3::fromPositionMatrix(wToL * position.toPositionMatrix()));
    }
    else {
        setLocalPosition(position);
    }
}

Vector3 GameObject::rotation()
{
    if(mCacheRotationValid)
        return mCacheRotation;

    if(mParent) {
        Matrix4 lToW = mParent->localToWorldMatrix();
        mCacheRotation = Vector3::fromRotationMatrix(lToW * mLocalRotation.toRotationMatrix());
    }
    else {
        mCacheRotation = mLocalRotation;
    }

    mCacheRotationValid = true;
    return mCacheRotation;
}

void GameObject::setRotation(const Vector3 &rotation)
{
    if(mParent) {
        Matrix4 wToL = mParent->worldToLocalMatrix();
        setLocalRotation(Vector3::fromRotationMatrix(wToL * rotation.toRotationMatrix()));
    }
    else {
        setLocalRotation(rotation);
    }
}

Vector3 GameObject::scale()
{
    if(mCacheScaleValid)
        return mCacheScale;

    if(mParent) {
        Matrix4 lToW = mParent->localToWorldMatrix();
        mCacheScale = Vector3::fromScaleMatrix(lToW * mLocalScale.toScaleMatrix());
    }
    else {
        mCacheScale = mLocalScale;
    }

    mCacheScaleValid = true;
    return mCacheScale;
}

void GameObject::setScale(const Vector3 &scale)
{
    if(mParent) {
        Matrix4 wToL = mParent->worldToLocalMatrix();
        setLocalScale(Vector3::fromScaleMatrix(wToL * scale.toScaleMatrix()));
    }
    else {
        setLocalScale(scale);
    }
}

Vector3 GameObject::localPosition() const
{
    return mLocalPosition;
}

void GameObject::setLocalPosition(const Vector3 &position)
{
    mLocalPosition = position;
    invalidateTransformCache(true, false, false, true);
}

Vector3 GameObject::localRotation() const
{
    return mLocalRotation;
}

void GameObject::setLocalRotation(const Vector3 &rotation)
{
    mLocalRotation = rotation;
    invalidateTransformCache(false, true, false, true);
}

Vector3 GameObject::localScale() const
{
    return mLocalScale;
}

void GameObject::setLocalScale(const Vector3 &scale)
{
    mLocalScale = scale;
    invalidateTransformCache(false, false, true, true);
}

Matrix4 GameObject::localToWorldMatrix()
{
    if(mCacheLToWValid)
        return mCacheLToW;

    Matrix4 tMatrix = mLocalPosition.toPositionMatrix();
    Matrix4 rMatrix = mLocalRotation.toRotationMatrix();
    Matrix4 sMatrix = mLocalScale.toScaleMatrix();
    Matrix4 m = tMatrix * rMatrix * sMatrix;

    if(mParent) {
        Matrix4 pMatrix = mParent->localToWorldMatrix();
        m = pMatrix * m;
    }

    mCacheLToW = m;
    mCacheLToWValid = true;
    return mCacheLToW;
}

Matrix4 GameObject::worldToLocalMatrix()
{
    if(mCacheWToLValid)
        return mCacheWToL;

    Matrix4 m = localToWorldMatrix();
    mCacheWToL = m.invert();
    mCacheWToLValid = true;
    return mCacheWToL;
}

Vector3 GameObject::forward()
{
    Matrix4 lToW = localToWorldMatrix();
    Matrix4 fM = Vector3::forward.toPositionMatrix();
    return (Vector3::fromPositionMatrix(lToW * fM) - position()).normalized();
}

Vector3 GameObject::right()
{
    Matrix4 lToW = localToWorldMatrix();
    Matrix4 fM = Vector3::right.toPositionMatrix();
    return (Vector3::fromPositionMatrix(lToW * fM) - position()).normalized();
}

Vector3 GameObject::up()
{
    Matrix4 lToW = localToWorldMatrix();
    Matrix4 fM = Vector3::up.toPositionMatrix();
    return (Vector3::fromPositionMatrix(lToW * fM) - position()).normalized();
}

Component *GameObject::getComponent(const std::string &name) const
{
    for(auto it = mComponents.begin(); it != mComponents.end(); ++it) {
        if((*it)->typeName() == name) {
            return *it;
        }
    }
    return 0;
}

Component *GameObject::addComponent(Component *component)
{
    component->mGameObject = this;
    mComponents.push_back(component);
    mComponentsChanged = true;
    return component;
}

void GameObject::removeComponent(Component *component)
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(), [component](const Ref<Component> &c) {
            return component == c;
    });
    if(it != mComponents.end()) {
        (*it)->mGameObject = 0;
        it = mComponents.erase(it);
        mComponentsChanged = true;
    }
}

std::vector<GameObject *> GameObject::recursiveFindGameObjects(const std::string &name)
{
    std::vector<GameObject*> objs;
    for(auto it = mIteratedChildren.begin(); it != mIteratedChildren.end(); ++it) {
        if((*it)->name() == name)
            objs.push_back(*it);
        std::vector<GameObject*> chObjs = (*it)->recursiveFindGameObjects(name);
        objs.insert(objs.end(), chObjs.begin(), chObjs.end());
    }
    return objs;
}

Component *GameObject::recursiveFindComponent(const std::string &typeName)
{
    Component *component = getComponent(typeName);
    if(component)
        return component;

    for(auto it = mIteratedChildren.begin(); it != mIteratedChildren.end(); ++it) {
        Component *c = (*it)->recursiveFindComponent(typeName);
        if(c)
            return c;
    }

    return 0;
}

void GameObject::invalidateTransformCache(bool position, bool rotation, bool scale, bool matrices)
{
    if(position)
        mCachePositionValid = false;
    if(rotation)
        mCacheRotationValid = false;
    if(scale)
        mCacheScaleValid = false;

    if(position || rotation || scale || matrices) {
        mCacheLToWValid = false;
        mCacheWToLValid = false;
    }

    for(auto it = mIteratedChildren.begin(); it != mIteratedChildren.end(); ++it) {
        (*it)->invalidateTransformCache(true, true, true, true);
    }
}

void GameObject::start()
{
    mStartCalled = true;

    if(mChildrenChanged) {
        mIteratedChildren.clear();
        for(auto it = mChildren.begin(); it != mChildren.end(); ++it) {
            mIteratedChildren.push_back(*it);
        }
        mChildrenChanged = false;
    }

    if(mComponentsChanged) {
        mIteratedComponents.clear();
        for(auto it = mComponents.begin(); it != mComponents.end(); ++it) {
            mIteratedComponents.push_back(*it);
        }
        mComponentsChanged = false;
    }

    for(auto it = mIteratedComponents.begin(); it != mIteratedComponents.end(); ++it) {
        if(!(*it)) continue;
        if(!(*it)->mStartCalled) {
            (*it)->start();
            (*it)->mStartCalled = true;
        }
    }

    for(auto it = mIteratedChildren.begin(); it != mIteratedChildren.end(); ++it) {
        if(!(*it)) continue;
        if(!(*it)->mStartCalled) {
            (*it)->start();
            (*it)->mStartCalled = true;
        }
    }
}

void GameObject::update(float deltaTime)
{
    if(mChildrenChanged) {
        mIteratedChildren.clear();
        for(auto it = mChildren.begin(); it != mChildren.end(); ++it) {
            mIteratedChildren.push_back(*it);
        }
        mChildrenChanged = false;
    }

    if(mComponentsChanged) {
        mIteratedComponents.clear();
        for(auto it = mComponents.begin(); it != mComponents.end(); ++it) {
            mIteratedComponents.push_back(*it);
        }
        mComponentsChanged = false;
    }

    if(mActive) {
        // Update components
        for(auto it = mIteratedComponents.begin(); it != mIteratedComponents.end(); ++it) {
            if(!(*it)) continue;
            if(!(*it)->mStartCalled) {
                (*it)->start();
                (*it)->mStartCalled = true;
            }
            (*it)->update(deltaTime);
        }
    }

    for(auto it = mIteratedChildren.begin(); it != mIteratedChildren.end(); ++it) {
        if(!(*it)) continue;
        if(!(*it)->mStartCalled) {
            (*it)->start();
            (*it)->mStartCalled = true;
        }
        (*it)->update(deltaTime);
    }
}

} // namespace cepp
