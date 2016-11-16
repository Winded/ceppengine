#pragma once

#include <ostream>
#include "../global.h"

namespace cepp {
class Matrix4;

class CEPP_DLL Vector3
{
    public:
        Vector3();
        Vector3(float px, float py);
        Vector3(float px, float py, float pz);

        /** Get vector length */
        float length() const;
        /** Get vector length squared (no sqrt called for better performance) */
        float sqrLength() const;

        /** Get the distance between this vector and the given vector. */
        float distanceTo(const Vector3 &otherVector) const;

        /** Dot product of this vector and given vector. */
        float dotProduct(const Vector3 &otherVector) const;

        /**
         * @brief Cross product of this vector and given vector.
         */
        Vector3 crossProduct(const Vector3 &otherVector) const;

        /**
         * @brief Return normalized version of this vector
         */
        Vector3 normalized() const;

        /**
         * @brief Returns whether this vector is within a box defined by given vectors.
         */
        bool isWithin(const Vector3 &v1, const Vector3 &v2);

        /**
         * @brief Convert position vector to matrix
         */
        Matrix4 toPositionMatrix() const;
        /**
         * @brief Convert matrix to position vector
         */
        static Vector3 fromPositionMatrix(const Matrix4 &mat);

        /**
         * @brief Convert rotation vector to matrix
         */
        Matrix4 toRotationMatrix() const;
        /**
         * @brief Convert matrix to rotation vector
         */
        static Vector3 fromRotationMatrix(const Matrix4 &mat);

        /**
         * @brief Convert scale vector to matrix
         */
        Matrix4 toScaleMatrix() const;
        /**
         * @brief Convert matrix to scale vector
         */
        static Vector3 fromScaleMatrix(const Matrix4 &mat);

        /**
         * @brief Perform line-plane intersection
         */
        static Vector3 linePlaneIntersection(const Vector3 &origin, const Vector3 &direction, const Vector3 &planeOrigin, const Vector3 &planeDirection);

        // Arithmetic operations
        Vector3 operator+(const Vector3 &otherVector) const;
        Vector3 operator-(const Vector3 &otherVector) const;
        Vector3 operator*(const Vector3 &otherVector) const;
        Vector3 operator/(const Vector3 &otherVector) const;

        Vector3 operator*(float value) const;
        Vector3 operator/(float value) const;

        Vector3 operator-() const;

        void operator+=(const Vector3 &otherVector);
        void operator-=(const Vector3 &otherVector);
        void operator*=(const Vector3 &otherVector);
        void operator/=(const Vector3 &otherVector);

        void operator*=(float value);
        void operator/=(float value);

        bool operator==(const Vector3 &otherVector) const;
        bool operator!=(const Vector3 &otherVector) const;
        bool operator<(const Vector3 &otherVector) const;
        bool operator>(const Vector3 &otherVector) const;
        bool operator<=(const Vector3 &otherVector) const;
        bool operator>=(const Vector3 &otherVector) const;

        // Actual coordinate values
        float x, y, z;

        // Static defaults
        static Vector3 zero;
        static Vector3 one;
        static Vector3 forward;
        static Vector3 backward;
        static Vector3 left;
        static Vector3 right;
        static Vector3 up;
        static Vector3 down;
};

inline Vector3 Vector3::operator+(const Vector3 &otherVector) const
{
    return Vector3(x + otherVector.x, y + otherVector.y, z + otherVector.z);
}

inline Vector3 Vector3::operator-(const Vector3 &otherVector) const
{
    return Vector3(x - otherVector.x, y - otherVector.y, z - otherVector.z);
}

inline Vector3 Vector3::operator*(const Vector3 &otherVector) const
{
    return Vector3(x * otherVector.x, y * otherVector.y, z * otherVector.z);
}

inline Vector3 Vector3::operator/(const Vector3 &otherVector) const
{
    return Vector3(x / otherVector.x, y / otherVector.y, z / otherVector.z);
}

inline Vector3 Vector3::operator*(float value) const
{
    return Vector3(x * value, y * value, z * value);
}

inline Vector3 Vector3::operator/(float value) const
{
    return Vector3(x / value, y / value, z / value);
}

inline Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

inline void Vector3::operator+=(const Vector3 &otherVector)
{
    x += otherVector.x; y += otherVector.y; z += otherVector.z;
}

inline void Vector3::operator-=(const Vector3 &otherVector)
{
    x -= otherVector.x; y -= otherVector.y; z -= otherVector.z;
}

inline void Vector3::operator*=(const Vector3 &otherVector)
{
    x *= otherVector.x; y *= otherVector.y; z *= otherVector.z;
}

inline void Vector3::operator/=(const Vector3 &otherVector)
{
    x /= otherVector.x; y /= otherVector.y; z /= otherVector.z;
}

inline void Vector3::operator*=(float value)
{
    x *= value; y *= value; z *= value;
}

inline void Vector3::operator/=(float value)
{
    x /= value; y /= value; z /= value;
}

inline bool Vector3::operator==(const Vector3 &otherVector) const
{
    return x == otherVector.x && y == otherVector.y && z == otherVector.z;
}

inline bool Vector3::operator!=(const Vector3 &otherVector) const
{
    return x != otherVector.x || y != otherVector.y || z != otherVector.z;
}

inline bool Vector3::operator<(const Vector3 &otherVector) const
{
    return x < otherVector.x && y < otherVector.y && z < otherVector.z;
}

inline bool Vector3::operator>(const Vector3 &otherVector) const
{
    return x > otherVector.x && y > otherVector.y && z > otherVector.z;
}

inline bool Vector3::operator<=(const Vector3 &otherVector) const
{
    return x <= otherVector.x && y <= otherVector.y && z <= otherVector.z;
}

inline bool Vector3::operator>=(const Vector3 &otherVector) const
{
    return x >= otherVector.x && y >= otherVector.y && z >= otherVector.z;
}

// ostream support
std::ostream &operator<<(std::ostream &stream, const Vector3 &vec);

}
