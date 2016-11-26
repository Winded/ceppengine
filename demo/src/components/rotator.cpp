#include "rotator.h"
#include <iostream>
#include <ceppengine/gameobject.h>

Rotator::Rotator() : mSpeed(45.f)
{

}

std::string Rotator::typeName() const
{
    return "Rotator";
}

float Rotator::speed() const
{
    return mSpeed;
}

void Rotator::setSpeed(float speed)
{
    mSpeed = speed;
}

void Rotator::start()
{
    std::cout << "START" << std::endl;
}

void Rotator::update(float deltaTime)
{
    cepp::Vector3 rot = gameObject()->rotation();
    rot.z += mSpeed * deltaTime;
    gameObject()->setRotation(rot);
}
