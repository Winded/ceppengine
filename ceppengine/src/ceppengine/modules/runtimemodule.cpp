#include "runtimemodule.h"

namespace cepp {

RuntimeModule::RuntimeModule() : mTime(0), mDeltaTime(0), mTimeScale(1.0f)
{

}

std::string RuntimeModule::name() const
{
    return "RuntimeModule";
}

float RuntimeModule::time() const
{
    return mTime;
}

float RuntimeModule::deltaTime() const
{
    return mDeltaTime;
}

float RuntimeModule::realDeltaTime() const
{
    return mDeltaTime / mTimeScale;
}

float RuntimeModule::timeScale() const
{
    return mTimeScale;
}

void RuntimeModule::setTimeScale(float timeScale)
{
    mTimeScale = timeScale;
}

void RuntimeModule::preUpdate(float deltaTime)
{
    mTime += deltaTime;
    mDeltaTime = deltaTime;
}

} // namespace cepp
