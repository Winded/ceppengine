#pragma once

#include "../gameobject.h"

namespace cepp {

/**
 * Components can be added to gameobjects to implement functionality, for example, to render a 3D shape for an object.
 */
class Component : public Object
{
    public:
        Component();
};

} // namespace cepp
