#include "portaudiomodule.h"
#include <algorithm>

namespace cepp {

PortAudioHandle::PortAudioHandle(PortAudioModule *module)
    : mModule(module), mClip(0), mStream(0)
{

}

AudioClip *PortAudioHandle::clip() const
{
    return mClip;
}

void PortAudioHandle::setClip(AudioClip *clip)
{
    if(mStream) {
        Pa_StopStream(mStream);
        Pa_CloseStreamm(mStream);
        mStream = 0;
    }

    mClip = clip;
    if(mClip) {
        PaError err = Pa_OpenDefaultStream(
                    &mStream,
                    0,
                    2,
                    paFloat32,
                    44100,
                    paFramesPerBufferUnspecified,
                    0, 0
        );
        assert(err == paNoError);
    }
}

float PortAudioHandle::volume() const
{
    // TODO
    return 0;
}

void PortAudioHandle::setVolume(float volume)
{
    // TODO
}

float PortAudioHandle::pitch() const
{
    // TODO
    return 0;
}

void PortAudioHandle::setPitch(float pitch)
{
    // TODO
}

float PortAudioHandle::pan() const
{
    // TODO
    return 0;
}

void PortAudioHandle::setPan(float pan)
{
    // TODO
}

bool PortAudioHandle::loop() const
{
    // TODO
    return false;
}

void PortAudioHandle::setLoop(bool loop)
{
    // TODO
}

bool PortAudioHandle::isPlaying() const
{
    return !Pa_IsStreamStopped(mStream);
}

void PortAudioHandle::play()
{
    Pa_StartStream(mStream);
}

void PortAudioHandle::pause()
{
    Pa_StopStream(mStream);
}

void PortAudioHandle::stop()
{
    Pa_AbortStream(mStream);
}

PortAudioModule::PortAudioModule()
{

}

IAudioHandle *PortAudioModule::createHandle()
{
    PortAudioHandle *handle = new PortAudioHandle(this);
    mHandles.push_back(handle);
    return handle;
}

void PortAudioModule::destroyHandle(IAudioHandle *handle)
{
    PortAudioHandle *h = (PortAudioHandle*)handle;

    auto it = std::find_if(mHandles.begin(), mHandles.end(), [h](const Ref<PortAudioHandle> &ph) {
        return ph == h;
    });
    if(it != mHandles.end()) {
        if(h->mStream) {
            Pa_AbortStream(h->mStream);
            Pa_CloseStream(h->mStream);
        }
        it = mHandles.erase(it);
    }
}

}
