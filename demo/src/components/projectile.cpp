#include "projectile.h"
#include <ceppengine/gameobject.h>
#include <ceppengine/scene.h>
#include "enemy.h"

using namespace cepp;

Projectile::Projectile()
    : mSpeed(1), mExplosionTime(0.5f), mExploded(false), mExplosionTimer(0), mExplosionDistance(0.1f), mTarget("Enemy")
{

}

std::string Projectile::typeName() const
{
    return "Projectile";
}

float Projectile::speed() const
{
    return mSpeed;
}

void Projectile::setSpeed(float speed)
{
    mSpeed = speed;
}

Vector3 Projectile::direction() const
{
    return mDirection;
}

void Projectile::setDirection(const Vector3 &direction)
{
    mDirection = direction.normalized();
}

Sprite *Projectile::explosionSprite() const
{
    return mExplosionSprite;
}

void Projectile::setExplosionSprite(Sprite *sprite)
{
    mExplosionSprite = sprite;
}

float Projectile::explosionTime() const
{
    return mExplosionTime;
}

void Projectile::setExplosionTime(float time)
{
    mExplosionTime = time;
}

float Projectile::range() const
{
    return mExplosionDistance;
}

void Projectile::setRange(float range)
{
    mExplosionDistance = range;
}

std::string Projectile::target() const
{
    return mTarget;
}

void Projectile::setTarget(const std::string &target)
{
    mTarget = target;
}

void Projectile::start()
{
    mRenderer = (SpriteRenderer*)gameObject()->getComponent("SpriteRenderer");
    mAudioSource = (AudioSource*)gameObject()->getComponent("AudioSource");
}

void Projectile::update(float deltaTime)
{
    if(mExploded) {
        mExplosionTimer += deltaTime;
        if(mExplosionTimer >= mExplosionTime) {
            gameObject()->destroy();
        }
    }
    else {
        Vector3 pos = gameObject()->position();
        pos += mDirection * mSpeed * deltaTime;
        gameObject()->setPosition(pos);

        std::vector<GameObject*> gObjects = gameObject()->scene()->findGameObjectsByName(mTarget);
        for(auto it = gObjects.begin(); it != gObjects.end(); ++it) {
            Vector3 targetPos = (*it)->position();
            Enemy *e = (Enemy*)((*it)->getComponent("Enemy"));
            if(pos.distanceTo(targetPos) <= mExplosionDistance && e && !e->isDead()) {
                mExploded = true;
                mExplosionTimer = 0;
                mRenderer->setSprite(mExplosionSprite);
                mAudioSource->play();
                e->die();
                break;
            }
        }
    }
}
