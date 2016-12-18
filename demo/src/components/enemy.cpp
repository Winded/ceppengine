#include "enemy.h"
#include "delayeddestruction.h"
#include "score.h"
#include <ceppengine/gameobject.h>
#include <ceppengine/scene.h>

using namespace cepp;

Enemy::Enemy() : mIsDead(false), mDeadTime(1.f)
{

}

std::string Enemy::typeName() const
{
    return "Enemy";
}

SpriteAnimation *Enemy::aliveAnimation() const
{
    return mAliveAnimation;
}

void Enemy::setAliveAnimation(SpriteAnimation *animation)
{
    mAliveAnimation = animation;
}

SpriteAnimation *Enemy::deadAnimation() const
{
    return mDeadAnimation;
}

void Enemy::setDeadAnimation(SpriteAnimation *animation)
{
    mDeadAnimation = animation;
}

float Enemy::deadTime() const
{
    return mDeadTime;
}

void Enemy::setDeadTime(float deadTime)
{
    mDeadTime = deadTime;
}

bool Enemy::isDead() const
{
    return mIsDead;
}

void Enemy::die()
{
    mIsDead = true;
    mAnimator->stop();
    mAnimator->setAnimation(mDeadAnimation);
    mAnimator->play();

    GameObject *scoreObj = gameObject()->scene()->findGameObjectByName("Score");
    if(scoreObj) {
        Score *score = (Score*)scoreObj->getComponent("Score");
        score->addScore(1);
    }

    DelayedDestruction *d = (DelayedDestruction*)gameObject()->addComponent(new DelayedDestruction());
    d->setDelay(mDeadTime);
}

void Enemy::start()
{
    mAnimator = (SpriteAnimator*)gameObject()->getComponent("SpriteAnimator");
    mAnimator->setAnimation(mAliveAnimation);
    mAnimator->play();
}
