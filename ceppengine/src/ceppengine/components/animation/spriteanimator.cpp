#include "spriteanimator.h"
#include "../../gameobject.h"

namespace cepp {

SpriteAnimator::SpriteAnimator() : mRenderer(0), mAutoPlay(false), mPlaying(false), mFrame(0), mFrameTime(0), mSpeed(1)
{

}

std::string SpriteAnimator::typeName() const
{
    return "SpriteAnimator";
}

SpriteAnimation *SpriteAnimator::animation() const
{
    return mAnimation;
}

void SpriteAnimator::setAnimation(SpriteAnimation *anim)
{
    mAnimation = anim;
    bool wasPlaying = mPlaying;
    stop();
    if(wasPlaying)
        play();
}

bool SpriteAnimator::autoPlay() const
{
    return mAutoPlay;
}

void SpriteAnimator::setAutoPlay(bool autoplay)
{
    mAutoPlay = autoplay;
}

int SpriteAnimator::currentFrame() const
{
    return mFrame;
}

float SpriteAnimator::currentFrameTime() const
{
    return mFrameTime;
}

void SpriteAnimator::play()
{
    mPlaying = true;
}

void SpriteAnimator::pause()
{
    mPlaying = false;
}

void SpriteAnimator::stop()
{
    mPlaying = false;
    mFrame = 0;
    mFrameTime = 0;
}

void SpriteAnimator::start()
{
    mRenderer = (SpriteRenderer*)gameObject()->getComponent("SpriteRenderer");
    assert(mRenderer);
    if(mAutoPlay)
        play();
}

void SpriteAnimator::update(float deltaTime)
{
    if(!mAnimation || !mPlaying) return;

    const SpriteAnimation::Frame *frame = mAnimation->getFrame(mFrame);
    if(!frame) return;

    mFrameTime += deltaTime;
    if(mFrameTime > frame->duration) {
        mFrameTime = 0;
        mFrame++;
        if(mFrame >= mAnimation->numFrames())
            mFrame = 0;
        frame = mAnimation->getFrame(mFrame);
        mRenderer->setSprite(frame->sprite);
    }
}

}
