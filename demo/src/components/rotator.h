#pragma once

#include <ceppengine/components/component.h>

class Rotator : public cepp::Component
{
    public:
        Rotator();

        virtual std::string typeName() const;

        float speed() const;
        void setSpeed(float speed);

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        float mSpeed;
};
