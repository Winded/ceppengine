#pragma once

#include <ceppengine/components/component.h>
#include <ceppengine/components/animation/spriteanimator.h>

class Enemy : public cepp::Component
{
    public:
        Enemy();

        virtual std::string typeName() const;

        cepp::SpriteAnimation *aliveAnimation() const;
        void setAliveAnimation(cepp::SpriteAnimation *animation);

        cepp::SpriteAnimation *deadAnimation() const;
        void setDeadAnimation(cepp::SpriteAnimation *animation);

        float deadTime() const;
        void setDeadTime(float deadTime);

        bool isDead() const;
        void die();

    protected:
        virtual void start();

    private:
        bool mIsDead;
        float mDeadTime;

        cepp::Ref<cepp::SpriteAnimator> mAnimator;

        cepp::Ref<cepp::SpriteAnimation> mAliveAnimation;
        cepp::Ref<cepp::SpriteAnimation> mDeadAnimation;
};
