#include "component.h"
#include "../gameobject.h"

namespace cepp {

Component::Component() : mGameObject(0), mStartCalled(false)
{

}

Component::~Component()
{

}

GameObject *Component::gameObject() const
{
    return mGameObject;
}

void Component::start()
{

}

void Component::update(float deltaTime)
{
    UNUSED_PARAM(deltaTime);
}

} // namespace cepp
