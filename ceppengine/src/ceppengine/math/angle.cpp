#include "angle.h"
#include <string>
#include "math.h"
#include "matrix4.h"

namespace cepp {

Angle::Angle()
    : x(0.f), y(0.f), z(0.f)
{
}

Angle::Angle(float px, float py, float pz)
    : x(px), y(py), z(pz)
{
}

Matrix4 Angle::toRotationMatrix() const
{
    Matrix4 xMatrix = Matrix4::identity;
    xMatrix.m22 = Math::cos(x * Math::deg2rad);
    xMatrix.m23 = -Math::sin(x * Math::deg2rad);
    xMatrix.m32 = Math::sin(x * Math::deg2rad);
    xMatrix.m33 = Math::cos(x * Math::deg2rad);

    Matrix4 yMatrix = Matrix4::identity;
    yMatrix.m11 = Math::cos(y * Math::deg2rad);
    yMatrix.m31 = -Math::sin(y * Math::deg2rad);
    yMatrix.m13 = Math::sin(y * Math::deg2rad);
    yMatrix.m33 = Math::cos(y * Math::deg2rad);

    Matrix4 zMatrix = Matrix4::identity;
    zMatrix.m11 = Math::cos(z * Math::deg2rad);
    zMatrix.m12 = -Math::sin(z * Math::deg2rad);
    zMatrix.m21 = Math::sin(z * Math::deg2rad);
    zMatrix.m22 = Math::cos(z * Math::deg2rad);

    Matrix4 mat = xMatrix * yMatrix * zMatrix;
    return mat;
}

Angle Angle::fromRotationMatrix(const Matrix4 &mat)
{
    // TODO: Fix. Not entirely working (problems with Y axis)
    Angle rot;
    rot.x = Math::atan2(mat.m32, mat.m33) * Math::rad2deg;
    rot.y = Math::atan2(-mat.m31, Math::sqrt(Math::pow(mat.m32, 2) + Math::pow(mat.m33, 2))) * Math::rad2deg;
    rot.z = Math::atan2(mat.m21, mat.m11) * Math::rad2deg;
    return rot;
}

Angle Angle::normalize() const
{
    Angle result = *this;

    while(result.x > 180)
        result.x -= 360;
    while(result.x < -179)
        result.x += 360;

    while(result.y > 180)
        result.y -= 360;
    while(result.y < -179)
        result.y += 360;

    while(result.z > 180)
        result.z -= 360;
    while(result.z < -179)
        result.z += 360;

    return result;
}

// Static defaults init
Angle Angle::zero(0.f, 0.f, 0.f);
Angle Angle::forward(0.f, 0.f, 0.f);
Angle Angle::backward(0.f, 180.f, 0.f);
Angle Angle::right(0.f, 90.f, 0.f);
Angle Angle::left(0.f, 270.f, 0.f);
Angle Angle::up(0.f, 0.f, 90.f);
Angle Angle::down(0.f, 0.f, 270.f);

}

std::ostream &operator<<(std::ostream &stream, const cepp::Angle &ang)
{
    stream << "[" << std::to_string(ang.x) << ", " << std::to_string(ang.y) << ", " << std::to_string(ang.z) << "]";
    return stream;
}
