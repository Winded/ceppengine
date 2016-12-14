#include "playermovement.h"
#include <iostream>
#include <ceppengine/gameobject.h>
#include <ceppengine/engine.h>

PlayerMovement::PlayerMovement() : mCanMove(true), mSpeed(1.f)
{

}

std::string PlayerMovement::typeName() const
{
    return "PlayerMovement";
}

bool PlayerMovement::canMove() const
{
    return mCanMove;
}

void PlayerMovement::setCanMove(bool canMove)
{
    mCanMove = canMove;
}

float PlayerMovement::speed() const
{
    return mSpeed;
}

void PlayerMovement::setSpeed(float speed)
{
    mSpeed = speed;
}

cepp::Vector3 PlayerMovement::minBounds() const
{
    return mMinBounds;
}

void PlayerMovement::setMinBounds(const cepp::Vector3 &bounds)
{
    mMinBounds = bounds;
}

cepp::Vector3 PlayerMovement::maxBounds() const
{
    return mMaxBounds;
}

void PlayerMovement::setMaxBounds(const cepp::Vector3 &bounds)
{
    mMaxBounds = bounds;
}

cepp::Vector3 PlayerMovement::movementDirection() const
{
    return mMovementDirection;
}

void PlayerMovement::update(float deltaTime)
{
    if(!mCanMove) return;

    cepp::Vector3 pos = gameObject()->position();

    if(cepp::Engine::instance()->inputModule()->isKeyDown('A') && pos.x > mMinBounds.x) {
        pos.x -= mSpeed * deltaTime;
    }
    else if(cepp::Engine::instance()->inputModule()->isKeyDown('D') && pos.x < mMaxBounds.x) {
        pos.x += mSpeed * deltaTime;
    }
    mMovementDirection = pos - gameObject()->position();

    gameObject()->setPosition(pos);
}
