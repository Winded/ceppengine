#include "audiosource.h"
#include "../../engine.h"

namespace cepp {

AudioSource::AudioSource() : mHandle(0), mVolume(1), mPitch(1), mPlayOnStart(false), mLoop(false)
{

}

AudioSource::~AudioSource()
{
}

std::string AudioSource::typeName() const
{
    return "AudioSource";
}

AudioClip *AudioSource::clip() const
{
    return mClip;
}

void AudioSource::setClip(AudioClip *clip)
{
    mClip = clip;
    if(mHandle)
        mHandle->setClip(clip);
}

float AudioSource::volume() const
{
    return mVolume;
}

void AudioSource::setVolume(float volume)
{
    mVolume = volume;
    if(mHandle)
        mHandle->setVolume(volume);
}

float AudioSource::pitch() const
{
    return mPitch;
}

void AudioSource::setPitch(float pitch)
{
    mPitch = pitch;
    if(mHandle)
        mHandle->setPitch(pitch);
}

bool AudioSource::playOnStart() const
{
    return mPlayOnStart;
}

void AudioSource::setPlayOnStart(bool playOnStart)
{
    mPlayOnStart = playOnStart;
}

bool AudioSource::loop() const
{
    return mLoop;
}

void AudioSource::setLoop(bool loop)
{
    mLoop = loop;
    if(mHandle)
        mHandle->setLoop(loop);
}

bool AudioSource::isPlaying() const
{
    if(mHandle)
        return mHandle->isPlaying();
    else
        return false;
}

void AudioSource::play()
{
    if(mHandle)
        mHandle->play();
}

void AudioSource::pause()
{
    if(mHandle)
        mHandle->pause();
}

void AudioSource::stop()
{
    if(mHandle)
        mHandle->stop();
}

void AudioSource::start()
{
    mHandle = Engine::instance()->audioModule()->createHandle();
    mHandle->setClip(mClip);
    mHandle->setVolume(mVolume);
    mHandle->setPitch(mPitch);
    mHandle->setLoop(mLoop);

    if(mPlayOnStart)
        play();
}

void AudioSource::onDestroyed()
{
    if(mHandle)
        Engine::instance()->audioModule()->destroyHandle(mHandle);
}

} // namespace cepp
