#include "playonpress.h"
#include <ceppengine/engine.h>
#include <ceppengine/gameobject.h>

PlayOnPress::PlayOnPress() : mAudio(0), mPlayButton('K')
{

}

std::string PlayOnPress::typeName() const
{
    return "PlayOnPress";
}

int PlayOnPress::playButton() const
{
    return mPlayButton;
}

void PlayOnPress::setPlayButton(int button)
{
    mPlayButton = button;
}

void PlayOnPress::start()
{
    mAudio = (cepp::AudioSource*)gameObject()->getComponent("AudioSource");
    mAudio->setLoop(true);
}

void PlayOnPress::update(float deltaTime)
{
    if(cepp::Engine::instance()->inputModule()->isKeyPressed(mPlayButton)) {
        if(mAudio->isPlaying())
            mAudio->pause();
        else
            mAudio->play();
    }
}
