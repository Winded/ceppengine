#pragma once

#include "../audiomodule.h"
#include "../../util/ref.h"
#include <AL/al.h>
#include <AL/alc.h>

namespace cepp {

class OpenALModule;

class OpenALAudioHandle : public IAudioHandle
{
    public:
        OpenALAudioHandle(OpenALModule *module);

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
        OpenALModule *mModule;

        AudioClip *mClip;
        ALuint mHandle;

        friend class OpenALModule;
};

struct OpenALClip
{
        AudioClip *clip;
        ALuint handle;
};

/**
 * Audio module using OpenAL
 */
class OpenALModule : public AudioModule
{
    public:
        OpenALModule();
        ~OpenALModule();

        virtual IAudioHandle *createHandle();
        virtual void destroyHandle(IAudioHandle *handle);

        virtual float masterVolume() const;
        virtual void setMasterVolume(float volume);

    protected:
        virtual void initialize();

    private:
        int getBuffer(AudioClip *clip);
        int updateBuffer(AudioClip *clip);

        std::vector<OpenALAudioHandle*> mHandles;
        std::vector<OpenALClip> mClips;
        ALCdevice *mDevice;
        ALCcontext *mContext;

        float mMasterVolume;

        friend class OpenALAudioHandle;
};

}
