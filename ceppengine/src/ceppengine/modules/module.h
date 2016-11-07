#pragma once

#include "../object.h"

namespace cepp {

class Module : public Object
{
    public:
        Module();

        virtual std::string name() const = 0;

    protected:
        virtual void initialize();
        virtual void preUpdate(float deltaTime);
        virtual void postUpdate(float deltaTime);

    private:

        friend class Engine;
};

} // namespace cepp
