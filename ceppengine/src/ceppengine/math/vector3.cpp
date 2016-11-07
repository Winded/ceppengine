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
    scale.x = Math::sqrt(mat.m11 * mat.m11 + mat.m12 * mat.m12 + mat.m13 * mat.m13);
    scale.y = Math::sqrt(mat.m21 * mat.m21 + mat.m22 * mat.m22 + mat.m23 * mat.m23);
    scale.z = Math::sqrt(mat.m31 * mat.m31 + mat.m32 * mat.m32 + mat.m33 * mat.m33);
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
