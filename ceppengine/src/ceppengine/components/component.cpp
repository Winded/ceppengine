#include "component.h"
#include "../gameobject.h"

namespace cepp {

Component::Component() : mGameObject(0), mStartCalled(false), mDestroyed(false)
{

}

Component::~Component()
{

}

GameObject *Component::gameObject() const
{
    return mGameObject;
}

bool Component::isDestroyed() const
{
    return mDestroyed;
}

void Component::destroy()
{
    mDestroyed = true;
    onDestroyed();
    if(gameObject()) {
        gameObject()->removeComponent(this);
    }
}

void Component::start()
{

}

void Component::update(float deltaTime)
{
    UNUSED_PARAM(deltaTime);
}

void Component::onDestroyed()
{
}

} // namespace cepp
