#pragma once

#include "vector3.h"
#include "angle.h"
#include "matrix4.h"

namespace cepp {

/**
 * Represents a transform in 3D space, assembled from position, rotation and scale.
 * Transform can have a parent transform for translating positions to global positions in hierarchies
 */
class Transform
{
    public:
        Transform();
        Transform(Vector3 pPosition, Angle pRotation, Vector3 pScale);

        Vector3 position;
        Angle rotation;
        Vector3 scale;
};

}
