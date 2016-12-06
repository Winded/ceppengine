#include "audiomodule.h"

namespace cepp {

AudioModule::AudioModule() : mMasterVolume(1.f)
{

}

float AudioModule::masterVolume() const
{
    return mMasterVolume;
}

void AudioModule::setMasterVolume(float volume)
{
    mMasterVolume = volume;
}

}
