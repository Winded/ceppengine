#pragma once

#include "playermovement.h"
#include <ceppengine/components/component.h>
#include <ceppengine/math/vector3.h>
#include <ceppengine/components/animation/spriteanimator.h>
#include <ceppengine/modules/inputmodule.h>
#include <ceppengine/components/audio/audiosource.h>

class PlayerWeapon : public cepp::Component
{
    public:
        PlayerWeapon();

        virtual std::string typeName() const;

        bool isShooting() const;

        int shootKey() const;
        void setShootKey(int key);

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        cepp::GameObject *makeProjectile();

        cepp::Ref<cepp::InputModule> mInputMod;
        cepp::Ref<cepp::AudioSource> mAudioSource;

        bool mShooting;
        int mShootKey;
};
