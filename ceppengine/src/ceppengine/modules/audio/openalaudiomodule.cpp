#include "openalaudiomodule.h"
#include <algorithm>

namespace cepp {

OpenALAudioHandle::OpenALAudioHandle(OpenALModule *module)
    : mModule(module), mClip(0), mHandle(0)
{

}

AudioClip *OpenALAudioHandle::clip() const
{
    return mClip;
}

void OpenALAudioHandle::setClip(AudioClip *clip)
{
    mClip = clip;
    if(mClip) {
        int alBuf = mModule->getBuffer(mClip);
        if(alBuf == 0)
            alBuf = mModule->updateBuffer(mClip);
        alSourcei(mHandle, AL_BUFFER, alBuf);
    }
    else {
        alSourcei(mHandle, AL_BUFFER, 0);
    }
}

float OpenALAudioHandle::volume() const
{
    float volume;
    alGetSourcef(mHandle, AL_GAIN, &volume);
    return volume;
}

void OpenALAudioHandle::setVolume(float volume)
{
    alSourcef(mHandle, AL_GAIN, volume);
}

float OpenALAudioHandle::pitch() const
{
    float pitch;
    alGetSourcef(mHandle, AL_PITCH, &pitch);
    return pitch;
}

void OpenALAudioHandle::setPitch(float pitch)
{
    alSourcef(mHandle, AL_PITCH, pitch);
}

float OpenALAudioHandle::pan() const
{
    // TODO
    return 0;
}

void OpenALAudioHandle::setPan(float pan)
{
    // TODO
}

bool OpenALAudioHandle::loop() const
{
    int loop;
    alGetSourcei(mHandle, AL_LOOPING, &loop);
    return loop > 0;
}

void OpenALAudioHandle::setLoop(bool loop)
{
    alSourcei(mHandle, AL_LOOPING, loop);
}

bool OpenALAudioHandle::isPlaying() const
{
    ALenum state;
    alGetSourcei(mHandle, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

void OpenALAudioHandle::play()
{
    alSourcePlay(mHandle);
}

void OpenALAudioHandle::pause()
{
    alSourcePause(mHandle);
}

void OpenALAudioHandle::stop()
{
    alSourceStop(mHandle);
}

OpenALModule::OpenALModule() : mDevice(0)
{

}

OpenALModule::~OpenALModule()
{
    for(auto it = mHandles.begin(); it != mHandles.end(); ++it) {
        delete *it;
    }
    mHandles.clear();
    if(mContext)
        alcDestroyContext(mContext);
    if(mDevice)
        alcCloseDevice(mDevice);
}

IAudioHandle *OpenALModule::createHandle()
{
    OpenALAudioHandle *handle = new OpenALAudioHandle(this);
    alGenSources(1, &(handle->mHandle));
    alSourcef(handle->mHandle, AL_GAIN, 1.f);
    mHandles.push_back(handle);
    return handle;
}

void OpenALModule::destroyHandle(IAudioHandle *handle)
{
    OpenALAudioHandle *h = (OpenALAudioHandle*)handle;

    auto it = std::find_if(mHandles.begin(), mHandles.end(), [h](OpenALAudioHandle *ph) {
        return ph == h;
    });
    if(it != mHandles.end()) {
        alSourceStop((*it)->mHandle);
        alDeleteSources(1, &((*it)->mHandle));
        it = mHandles.erase(it);
    }
}

void OpenALModule::initialize()
{
    mDevice = alcOpenDevice(0);
    if(!mDevice) {
        fprintf(stderr, "OpenALModule: Failed to initialize OpenAL device!");
        return;
    }

    mContext = alcCreateContext(mDevice, 0);
    if(!alcMakeContextCurrent(mContext)) {
        fprintf(stderr, "OpenALModule: Failed to initialize OpenAL device!");
        alcDestroyContext(mContext);
        alcCloseDevice(mDevice);
        return;
    }
}

int OpenALModule::getBuffer(AudioClip *clip)
{
    auto it = std::find_if(mClips.begin(), mClips.end(), [clip](const OpenALClip &aClip) {
       return aClip.clip == clip;
    });
    if(it != mClips.end())
        return (*it).handle;
    else
        return 0;
}

int OpenALModule::updateBuffer(AudioClip *clip)
{
    auto it = std::find_if(mClips.begin(), mClips.end(), [clip](const OpenALClip &aClip) {
       return aClip.clip == clip;
    });
    if(it != mClips.end()) {
        alDeleteBuffers(1, &((*it).handle));
        it = mClips.erase(it);
    }

    ALuint alBuf;

    alGenBuffers(1, &alBuf);

    ALenum format =
            clip->numChannels() == 1 && clip->bitsPerSample() == 8 ? AL_FORMAT_MONO8 :
            clip->numChannels() == 1 && clip->bitsPerSample() == 16 ? AL_FORMAT_MONO16 :
            clip->numChannels() == 2 && clip->bitsPerSample() == 8 ? AL_FORMAT_STEREO8 :
            clip->numChannels() == 2 && clip->bitsPerSample() == 16 ? AL_FORMAT_STEREO16 :
            0;

    alBufferData(alBuf, format, clip->data(), clip->dataSize(), clip->sampleRate());

    ALenum err = alGetError();
    if(err != AL_NO_ERROR) {
        fprintf(stderr, "OpenAL Error: %i", err);
    }

    OpenALClip aClip;
    aClip.clip = clip;
    aClip.handle = alBuf;
    mClips.push_back(aClip);
    return alBuf;
}

}
