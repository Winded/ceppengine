#include "transform.h"
#include "math.h"

namespace cepp {

Transform::Transform()
    : position(Vector3::zero), rotation(Angle::zero), scale(Vector3::one)
{
}

Transform::Transform(Vector3 pPosition, Angle pRotation, Vector3 pScale)
    : position(pPosition), rotation(pRotation), scale(pScale)
{
}

}
