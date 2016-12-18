#pragma once

#include <ceppengine/components/component.h>
#include <ceppengine/gameobject.h>

class EnemySpawner : public cepp::Component
{
    public:
        EnemySpawner();

        virtual std::string typeName() const;

        float spawnFrequency() const;
        void setSpawnFrequency(float frequency);

        float minOffset() const;
        float maxOffset() const;
        void setMinMaxOffset(float min, float max);

    protected:
        virtual void update(float deltaTime);

    private:
        cepp::GameObject *makeEnemy();

        float mSpawnFrequency, mSpawnTimer;
        float mMinOffset, mMaxOffset;
};
