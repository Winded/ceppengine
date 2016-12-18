#include "playeranimations.h"
#include <iostream>
#include <ceppengine/gameobject.h>
#include <ceppengine/engine.h>

using namespace cepp;

PlayerAnimations::PlayerAnimations() : mFlipped(false)
{

}

std::string PlayerAnimations::typeName() const
{
    return "PlayerAnimations";
}

SpriteAnimation *PlayerAnimations::idleAnimation() const
{
    return mIdleAnimation;
}

void PlayerAnimations::setIdleAnimation(SpriteAnimation *animation)
{
    mIdleAnimation = animation;
}

SpriteAnimation *PlayerAnimations::moveAnimation() const
{
    return mMoveAnimation;
}

void PlayerAnimations::setMoveAnimation(SpriteAnimation *animation)
{
    mMoveAnimation = animation;
}

SpriteAnimation *PlayerAnimations::shootAnimation() const
{
    return mShootAnimation;
}

void PlayerAnimations::setShootAnimation(SpriteAnimation *animation)
{
    mShootAnimation = animation;
}

void PlayerAnimations::start()
{
    mAnimator = (SpriteAnimator*)gameObject()->getComponent("SpriteAnimator");
    mMovement = (PlayerMovement*)gameObject()->getComponent("PlayerMovement");
    mWeapon = (PlayerWeapon*)gameObject()->getComponent("PlayerWeapon");
    assert(mAnimator && mMovement);
}

void PlayerAnimations::update(float deltaTime)
{
    Vector3 moveDir = mMovement->movementDirection();

    if(moveDir.x != 0) {
        mFlipped = moveDir.x > 0;
        if(mFlipped)
            gameObject()->setLocalScale(Vector3(-1, 1, 1));
        else
            gameObject()->setLocalScale(Vector3(1, 1, 1));
    }

    if(mWeapon->isShooting() && mAnimator->animation() != mShootAnimation) {
        mAnimator->stop();
        mAnimator->setAnimation(mShootAnimation);
        mAnimator->play();
    }
    else if(!mAnimator->isPlaying()) {
        mAnimator->stop();
        mAnimator->setAnimation(mIdleAnimation);
        mAnimator->play();
    }
}
