#pragma once

#include "../global.h"
#include <ostream>

namespace cepp {

class Matrix4;

/**
 * @brief Simple structure resresenting Euler angles. Values represent rotation along axis (in degrees).
 */
class CEPP_DLL Angle
{
    public:
        Angle();
        Angle(float px, float py, float pz);

        /**
         * @brief Convert to rotation matrix
         */
        Matrix4 toRotationMatrix() const;
        /**
         * @brief Create euler angles from matrix
         */
        static Angle fromRotationMatrix(const Matrix4 &mat);

        // Arithmetic operations
        Angle operator+(const Angle &otherAngle);
        Angle operator-(const Angle &otherAngle);
        Angle operator*(const Angle &otherAngle);
        Angle operator/(const Angle &otherAngle);

        Angle operator*(float value);
        Angle operator/(float value);

        bool operator==(const Angle &otherAngle) const;
        bool operator!=(const Angle &otherAngle) const;

        /**
         * @brief Clamp axes to range between -179 and 180
         */
        Angle normalize() const;

        float x, y, z;

        // Static defaults
        static Angle zero;
        static Angle forward;
        static Angle backward;
        static Angle right;
        static Angle left;
        static Angle up;
        static Angle down;
};

inline Angle Angle::operator+(const Angle &otherAngle)
{
    return Angle(x + otherAngle.x, y + otherAngle.y, z + otherAngle.z);
}

inline Angle Angle::operator-(const Angle &otherAngle)
{
    return Angle(x - otherAngle.x, y - otherAngle.y, z - otherAngle.z);
}

inline Angle Angle::operator*(const Angle &otherAngle)
{
    return Angle(x * otherAngle.x, y * otherAngle.y, z * otherAngle.z);
}

inline Angle Angle::operator/(const Angle &otherAngle)
{
    return Angle(x / otherAngle.x, y / otherAngle.y, z / otherAngle.z);
}

inline Angle Angle::operator*(float value)
{
    return Angle(x * value, y * value, z * value);
}

inline Angle Angle::operator/(float value)
{
    return Angle(x / value, y / value, z / value);
}

inline bool Angle::operator==(const Angle &otherAngle) const
{
    return x == otherAngle.x && y == otherAngle.y && z == otherAngle.z;
}

inline bool Angle::operator!=(const Angle &otherAngle) const
{
    return x != otherAngle.x || y != otherAngle.y || z != otherAngle.z;
}

}

// ostream support
std::ostream &operator<<(std::ostream &stream, const cepp::Angle &ang);
