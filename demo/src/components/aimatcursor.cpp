#include "aimatcursor.h"
#include <ceppengine/engine.h>
#include <ceppengine/math/math.h>
#include <iostream>

AimAtCursor::AimAtCursor() : mInputMod(0)
{

}

std::string AimAtCursor::typeName() const
{
    return "AimAtCursor";
}

void AimAtCursor::start()
{
    mInputMod = cepp::Engine::instance()->inputModule();
}

void AimAtCursor::update(float deltaTime)
{
    cepp::Camera *camera = gameObject()->scene()->mainCamera();
    cepp::Vector3 cursorWorld = camera->screenToWorldPosition(mInputMod->mousePosition());
    cursorWorld.z = gameObject()->position().z;
    cepp::Vector3 dir = (cursorWorld - gameObject()->position()).normalized();
    float angle = cepp::Math::atan2(dir.y, dir.x) * cepp::Math::rad2deg;
    cepp::Vector3 ang(0, 0, angle);
    gameObject()->setRotation(ang);
}
