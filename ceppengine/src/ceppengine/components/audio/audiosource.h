#pragma once

#include "../component.h"
#include "../../modules/audiomodule.h"
#include "../../util/ref.h"

namespace cepp {

/**
 * Audio source can play audio from an audio clip
 */
class AudioSource : public Component
{
    public:
        AudioSource();
        ~AudioSource();

        virtual std::string typeName() const;

        AudioClip *clip() const;
        void setClip(AudioClip *clip);

        float volume() const;
        void setVolume(float volume);

        float pitch() const;
        void setPitch(float pitch);

        bool playOnStart() const;
        void setPlayOnStart(bool playOnStart);

        bool loop() const;
        void setLoop(bool loop);

        bool isPlaying() const;

        void play();
        void pause();
        void stop();

    protected:
        virtual void start();

    private:
        IAudioHandle *mHandle;

        Ref<AudioClip> mClip;

        float mVolume, mPitch;
        bool mPlayOnStart, mLoop;
};

} // namespace cepp
