#pragma once

#include <ceppengine/components/component.h>

class DelayedDestruction : public cepp::Component
{
    public:
        DelayedDestruction();

        virtual std::string typeName() const;

        float delay() const;
        void setDelay(float delay);

    protected:
        virtual void update(float deltaTime);

    private:
        float mDelay, mTimer;
};
