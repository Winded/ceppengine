#pragma once

#include <ceppengine/components/component.h>

namespace cepp {

class FPSPrint : public Component
{
    public:
        FPSPrint();

        virtual std::string typeName() const;

    protected:
        virtual void update(float deltaTime);
};

}
