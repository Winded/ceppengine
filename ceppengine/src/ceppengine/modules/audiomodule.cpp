#include "audiomodule.h"

namespace cepp {

AudioModule::AudioModule() : mMasterVolume(1.f)
{

}

std::string AudioModule::name() const
{
    return "AudioModule";
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
