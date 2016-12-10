#pragma once

#include "../component.h"
#include "../rendering/spriterenderer.h"
#include "../../assets/spriteanimation.h"
#include "../../util/ref.h"

namespace cepp {

/**
 * The sprite animator can be used to play animations by changing sprite renderer's sprite.
 */
class SpriteAnimator : public Component
{
    public:
        SpriteAnimator();

        virtual std::string typeName() const;

        SpriteAnimation *animation() const;
        void setAnimation(SpriteAnimation *anim);

        bool autoPlay() const;
        void setAutoPlay(bool autoplay);

        int currentFrame() const;
        float currentFrameTime() const;

        void play();
        void pause();
        void stop();

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        SpriteRenderer *mRenderer;

        bool mAutoPlay;

        Ref<SpriteAnimation> mAnimation;
        bool mPlaying;
        int mFrame;
        float mFrameTime;
        float mSpeed;
};

}
