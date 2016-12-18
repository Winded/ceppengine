#pragma once

#include <ceppengine/components/component.h>
#include <ceppengine/math/vector3.h>
#include <ceppengine/components/rendering/spriterenderer.h>
#include <ceppengine/components/audio/audiosource.h>

class Projectile : public cepp::Component
{
    public:
        Projectile();

        virtual std::string typeName() const;

        float speed() const;
        void setSpeed(float speed);

        cepp::Vector3 direction() const;
        void setDirection(const cepp::Vector3 &direction);

        cepp::Sprite *explosionSprite() const;
        void setExplosionSprite(cepp::Sprite *sprite);

        float explosionTime() const;
        void setExplosionTime(float time);

        float range() const;
        void setRange(float range);

        std::string target() const;
        void setTarget(const std::string &target);

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        cepp::Ref<cepp::SpriteRenderer> mRenderer;
        cepp::Ref<cepp::AudioSource> mAudioSource;

        bool mExploded;
        float mSpeed, mExplosionTime, mExplosionTimer, mExplosionDistance;
        cepp::Vector3 mDirection;
        cepp::Ref<cepp::Sprite> mExplosionSprite;
        std::string mTarget;
};
