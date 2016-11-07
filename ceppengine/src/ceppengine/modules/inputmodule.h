#pragma once

#include "module.h"
#include "../math/vector3.h"

namespace cepp {

/**
 * Input module handles input, such as keyboard and mouse, and touch on mobile.
 */
class InputModule : public Module
{
public:
    InputModule();

    virtual Vector3 mousePosition() const = 0;

    virtual float mouseScrollDelta() const = 0;

    virtual bool isKeyPressed(int key) const = 0;
    virtual bool isKeyDown(int key) const = 0;
    virtual bool isKeyReleased(int key) const = 0;

    virtual bool isMouseButtonPressed(int key) const = 0;
    virtual bool isMouseButtonDown(int key) const = 0;
    virtual bool isMouseButtonReleased(int key) const = 0;
};

} // namespace cepp
