#pragma once

#include <ceppengine/components/component.h>
#include <ceppengine/modules/inputmodule.h>

class AimAtCursor : public cepp::Component
{
    public:
        AimAtCursor();

        virtual std::string typeName() const;

    protected:
        virtual void start();
        virtual void update(float deltaTime);

    private:
        cepp::InputModule *mInputMod;
};
