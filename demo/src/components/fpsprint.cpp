#include "fpsprint.h"

namespace cepp {

FPSPrint::FPSPrint()
{

}

std::string FPSPrint::typeName() const
{
    return "FPSPrint";
}

void FPSPrint::update(float deltaTime)
{
    float fps = 1.f / deltaTime;
    printf("FPS: %f\n", fps);
}

}
