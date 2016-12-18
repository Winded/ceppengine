#include "vector3.h"
#include "matrix4.h"
#include "math.h"
#include <string>

namespace cepp {

Vector3::Vector3()
    : x(0.f), y(0.f), z(0.f)
{
}

Vector3::Vector3(float px, float py)
    : x(px), y(py), z(0.f)
{
}

Vector3::Vector3(float px, float py, float pz)
    : x(px), y(py), z(pz)
{
}

float Vector3::length() const
{
    return Math::sqrt(x * x + y * y + z * z);
}

float Vector3::sqrLength() const
{
    return (x * x + y * y + z * z);
}

float Vector3::distanceTo(const Vector3 &otherVector) const
{
    return (otherVector - (*this)).length();
}

float Vector3::dotProduct(const Vector3 &otherVector) const
{
    return x * otherVector.x + y * otherVector.y + z * otherVector.z;
}

Vector3 Vector3::crossProduct(const Vector3 &otherVector) const
{
    Vector3 result;
    result.x = y * otherVector.z - z * otherVector.y;
    result.y = z * otherVector.x - x * otherVector.z;
    result.z = x * otherVector.y - y * otherVector.x;
    return result;
}

Vector3 Vector3::normalized() const
{
    Vector3 v;
    float len = length();
    v.x = x / len;
    v.y = y / len;
    v.z = z / len;
    return v;
}

bool Vector3::isWithin(const Vector3 &v1, const Vector3 &v2)
{
    Vector3 myVec = (*this);
    Vector3 cross1 = v1.crossProduct(myVec);
    Vector3 cross2 = v1.crossProduct(v2);
    Vector3 cross3 = v2.crossProduct(myVec);
    Vector3 cross4 = v2.crossProduct(v1);
    return (cross1 * cross2 >= Vector3::zero && cross3 * cross4 >= Vector3::zero);
}

Matrix4 Vector3::toPositionMatrix() const
{
    Matrix4 m = Matrix4::identity;
    m.m14 = x;
    m.m24 = y;
    m.m34 = z;
    return m;
}

Vector3 Vector3::fromPositionMatrix(const Matrix4 &mat)
{
    Vector3 vec;
    vec.x = mat.m14;
    vec.y = mat.m24;
    vec.z = mat.m34;
    return vec;
}

Matrix4 Vector3::toRotationMatrix() const
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

Vector3 Vector3::fromRotationMatrix(const Matrix4 &mat)
{
    // Not perfect. Problems with Y axis.
    Vector3 rot;
    rot.x = Math::atan2(mat.m32, mat.m33) * Math::rad2deg;
    rot.y = Math::atan2(-mat.m31, Math::sqrt(Math::pow(mat.m32, 2) + Math::pow(mat.m33, 2))) * Math::rad2deg;
    rot.z = Math::atan2(mat.m21, mat.m11) * Math::rad2deg;
    return rot;
}

Matrix4 Vector3::toScaleMatrix() const
{
    Matrix4 m = Matrix4::identity;
    m.m11 = x;
    m.m22 = y;
    m.m33 = z;
    return m;
}

Vector3 Vector3::fromScaleMatrix(const Matrix4 &mat)
{
    Vector3 scale;
    scale.x = mat.m11 + mat.m12 + mat.m13 + mat.m14;
    scale.y = mat.m21 + mat.m22 + mat.m23 + mat.m24;
    scale.z = mat.m31 + mat.m32 + mat.m33 + mat.m34;
    return scale;
}

Vector3 Vector3::linePlaneIntersection(const Vector3 &origin, const Vector3 &direction, const Vector3 &planeOrigin, const Vector3 &planeDirection)
{
    Vector3 linePoint2 = origin + direction;
    float x = planeDirection.dotProduct(planeOrigin - origin) / planeDirection.dotProduct(linePoint2 - origin);
    Vector3 vec = origin + (linePoint2 - origin) * x;
    return vec;
}

// Static defaults init
Vector3 Vector3::zero(0.f, 0.f, 0.f);
Vector3 Vector3::one(1.f, 1.f, 1.f);
Vector3 Vector3::forward(0.f, 0.f, 1.f);
Vector3 Vector3::backward(0.f, 0.f, -1.f);
Vector3 Vector3::right(1.f, 0.f, 0.f);
Vector3 Vector3::left(-1.f, 0.f, 0.f);
Vector3 Vector3::up(0.f, 1.f, 0.f);
Vector3 Vector3::down(0.f, -1.f, 0.f);

std::ostream &operator<<(std::ostream &stream, const Vector3 &vec)
{
    stream << "[" << std::to_string(vec.x) << ", " << std::to_string(vec.y) << ", " << std::to_string(vec.z) << "]";
    return stream;
}

}
