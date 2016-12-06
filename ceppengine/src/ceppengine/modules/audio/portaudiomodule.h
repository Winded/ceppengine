#pragma once

#include "../audiomodule.h"
#include "../../util/ref.h"
#include <portaudio.h>

namespace cepp {

class PortAudioModule;

class PortAudioHandle : public IAudioHandle
{
    public:
        PortAudioHandle(PortAudioModule *module);

        virtual AudioClip *clip() const;
        virtual void setClip(AudioClip *clip);

        virtual float volume() const;
        virtual void setVolume(float volume);

        virtual float pitch() const;
        virtual void setPitch(float pitch);

        virtual float pan() const;
        virtual void setPan(float pan);

        virtual bool loop() const;
        virtual void setLoop(bool loop);

        virtual bool isPlaying() const;

        virtual void play();
        virtual void pause();
        virtual void stop();

    private:
        PortAudioModule *mModule;

        AudioClip *mClip;
        PaStream *mStream;

        friend class PortAudioModule;
};

/**
 * Audio module for PortAudio, a cross-platform audio library
 */
class PortAudioModule : public AudioModule
{
    public:
        PortAudioModule();

        virtual IAudioHandle *createHandle();
        virtual void destroyHandle(IAudioHandle *handle);

    private:
        std::vector<Ref<PortAudioHandle>> mHandles;
};

}
