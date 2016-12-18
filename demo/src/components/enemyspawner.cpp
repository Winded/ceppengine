#include "enemyspawner.h"
#include <ceppengine/components/rendering/spriterenderer.h>
#include "enemy.h"
#include <ceppengine/engine.h>
#include <ceppengine/math/math.h>

using namespace cepp;

EnemySpawner::EnemySpawner() : mSpawnFrequency(1.f), mSpawnTimer(0), mMinOffset(-3.f), mMaxOffset(3.f)
{

}

std::string EnemySpawner::typeName() const
{
    return "EnemySpawner";
}

float EnemySpawner::spawnFrequency() const
{
    return mSpawnFrequency;
}

void EnemySpawner::setSpawnFrequency(float frequency)
{
    mSpawnFrequency = frequency;
}

float EnemySpawner::minOffset() const
{
    return mMinOffset;
}

float EnemySpawner::maxOffset() const
{
    return mMaxOffset;
}

void EnemySpawner::setMinMaxOffset(float min, float max)
{
    mMinOffset = min;
    mMaxOffset = max;
}

void EnemySpawner::update(float deltaTime)
{
    mSpawnTimer += deltaTime;

    if(mSpawnTimer >= mSpawnFrequency) {
        GameObject *enemy = makeEnemy();
        enemy->setParent(gameObject());
        Vector3 pos;
        pos.x = mMinOffset + ((float)(rand() % 100) / 100.f) * (mMaxOffset - mMinOffset);
        enemy->setLocalPosition(pos);
        mSpawnTimer = 0;
    }
}

GameObject *EnemySpawner::makeEnemy()
{
    GameObject *enemyObj = new GameObject("Enemy");
    enemyObj->addComponent(new SpriteRenderer());
    enemyObj->addComponent(new SpriteAnimator());
    Enemy *e = (Enemy*)enemyObj->addComponent(new Enemy());
    e->setAliveAnimation((SpriteAnimation*)Engine::instance()->assetLoader()->loadAsset("/enemy_alive.spriteanim", "SpriteAnimation"));
    e->setDeadAnimation((SpriteAnimation*)Engine::instance()->assetLoader()->loadAsset("/enemy_dead.spriteanim", "SpriteAnimation"));
    e->setDeadTime(1.5f);
    return enemyObj;
}
