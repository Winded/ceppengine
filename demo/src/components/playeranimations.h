#pragma once

#include "playermovement.h"
#include <ceppengine/components/component.h>
#include <ceppengine/math/vector3.h>
#include <ceppengine/components/animation/spriteanimator.h>

class PlayerAnimations : public cepp::Component
{
    public:
        PlayerAnimations();

        virtual std::string typeName() const;

        cepp::SpriteAnimation *idleAnimation() const;
        void setIdleAnimation(cepp::SpriteAnimation *animation);

        cepp::SpriteAnimation *moveAnimation() const;
        void setMoveAnimation(cepp::SpriteAnimation *animation);

        cepp::SpriteAnimation *shootAnimation() const;
        void setShootAnimation(cepp::SpriteAnimation *animation);

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        bool mFlipped;

        cepp::Ref<PlayerMovement> mMovement;

        cepp::Ref<cepp::SpriteAnimator> mAnimator;
        cepp::Ref<cepp::SpriteAnimation> mIdleAnimation;
        cepp::Ref<cepp::SpriteAnimation> mMoveAnimation;
        cepp::Ref<cepp::SpriteAnimation> mShootAnimation;
};
