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
    assert(mAnimator && mMovement);
}

void PlayerAnimations::update(float deltaTime)
{
    Vector3 moveDir = mMovement->movementDirection();

    if(moveDir.x != 0) {
        // Animation change
        mFlipped = moveDir.x < 0;
    }
    else {
        // Animation change

    }

    if(mFlipped)
        gameObject()->setScale(Vector3(-1, 1, 1));
    else
        gameObject()->setScale(Vector3(1, 1, 1));
}
