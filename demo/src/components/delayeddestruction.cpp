#include "delayeddestruction.h"
#include <ceppengine/gameobject.h>

DelayedDestruction::DelayedDestruction() : mDelay(1), mTimer(0)
{

}

std::string DelayedDestruction::typeName() const
{
    return "DelayedDestruction";
}

float DelayedDestruction::delay() const
{
    return mDelay;
}

void DelayedDestruction::setDelay(float delay)
{
    mDelay = delay;
}

void DelayedDestruction::update(float deltaTime)
{
    mTimer += deltaTime;

    if(mTimer >= mDelay) {
        gameObject()->destroy();
    }
}
