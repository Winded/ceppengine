#include "playerweapon.h"
#include <iostream>
#include <ceppengine/gameobject.h>
#include <ceppengine/engine.h>
#include "projectile.h"
#include "delayeddestruction.h"

using namespace cepp;

PlayerWeapon::PlayerWeapon() : mShooting(false), mShootKey(' ')
{

}

std::string PlayerWeapon::typeName() const
{
    return "PlayerWeapon";
}

bool PlayerWeapon::isShooting() const
{
    return mShooting;
}

int PlayerWeapon::shootKey() const
{
    return mShootKey;
}

void PlayerWeapon::setShootKey(int key)
{
    mShootKey = key;
}

void PlayerWeapon::start()
{
    mInputMod = Engine::instance()->inputModule();
    mAudioSource = (AudioSource*)gameObject()->getComponent("AudioSource");
}

void PlayerWeapon::update(float deltaTime)
{
    mShooting = false;

    if(mInputMod->isKeyPressed(mShootKey)) {
        GameObject *proj = makeProjectile();
        proj->setParent(gameObject()->scene()->rootObject());
        proj->setPosition(gameObject()->position() + (-gameObject()->right()) * 0.2f + Vector3(0, 0.1f, 0));
        mAudioSource->play();
        mShooting = true;
    }
}

GameObject *PlayerWeapon::makeProjectile()
{
    GameObject *go = new GameObject("Projectile");
    SpriteRenderer *r = (SpriteRenderer*)go->addComponent(new SpriteRenderer());
    r->setSprite((Sprite*)Engine::instance()->assetLoader()->loadAsset("/projectile.sprite", "Sprite"));
    AudioSource *audio = (AudioSource*)go->addComponent(new AudioSource());
    audio->setClip((AudioClip*)Engine::instance()->assetLoader()->loadAsset("/explosion.wav", "AudioClip"));
    Projectile *p = (Projectile*)go->addComponent(new Projectile());
    p->setDirection(-(gameObject()->right()));
    p->setRange(0.5f);
    p->setSpeed(5.f);
    p->setExplosionSprite((Sprite*)Engine::instance()->assetLoader()->loadAsset("/projectile_explosion.sprite", "Sprite"));
    p->setTarget("Enemy");
    DelayedDestruction *d = (DelayedDestruction*)go->addComponent(new DelayedDestruction());
    d->setDelay(5.0f);
    return go;
}
