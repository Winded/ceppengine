#pragma once

#include "module.h"
#include "../assets/audioclip.h"

namespace cepp {

class IAudioHandle
{
    public:
        virtual AudioClip *clip() const = 0;
        virtual void setClip(AudioClip *clip) = 0;

        virtual float volume() const = 0;
        virtual void setVolume(float volume) = 0;

        virtual float pitch() const = 0;
        virtual void setPitch(float pitch) = 0;

        virtual float pan() const = 0;
        virtual void setPan(float pan) = 0;

        virtual bool loop() const = 0;
        virtual void setLoop(bool loop) = 0;

        virtual bool isPlaying() const = 0;

        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
};

class AudioModule : public Module
{
    public:
        AudioModule();

        float masterVolume() const;
        void setMasterVolume(float volume);

        virtual IAudioHandle *createHandle() = 0;
        virtual void destroyHandle(IAudioHandle *handle) = 0;

    private:
        float mMasterVolume;
};

}
