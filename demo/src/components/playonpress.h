#pragma once

#include <ceppengine/components/component.h>
#include <ceppengine/components/audio/audiosource.h>

class PlayOnPress : public cepp::Component
{
    public:
        PlayOnPress();

        virtual std::string typeName() const;

        int playButton() const;
        void setPlayButton(int button);

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        cepp::AudioSource *mAudio;
        int mPlayButton;
};
