#include "runtimemodule.h"

namespace cepp {

RuntimeModule::RuntimeModule() : mTime(0), mDeltaTime(0), mTimeScale(1.0f)
{

}

float RuntimeModule::time() const
{
    return mTime;
}

float RuntimeModule::deltaTime() const
{
    return mDeltaTime * mTimeScale;
}

float RuntimeModule::realDeltaTime() const
{
    return mDeltaTime;
}

float RuntimeModule::timeScale() const
{
    return mTimeScale;
}

void RuntimeModule::setTimeScale(float timeScale)
{
    mTimeScale = timeScale;
}

} // namespace cepp
