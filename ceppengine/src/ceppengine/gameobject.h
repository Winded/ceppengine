#pragma once

#include <string>
#include "object.h"

namespace cepp {

class GameObject : public Object
{
    public:
        GameObject();
        GameObject(std::string name);

        std::string name() const;
        void setName(std::string name);

    private:
        std::string mName;
};

} // namespace cepp
