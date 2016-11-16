#pragma once

#include "vector3.h"

namespace cepp{

class Matrix4
{
    public:
        Matrix4();
        Matrix4(float values[]);

        // Matrix multiplication
        Matrix4 operator*(const Matrix4 &mat) const;

        float determinant() const;

        /**
         * @brief Multiply this matrix with given matrix, return result
         */
        Matrix4 multiply(const Matrix4 &mat) const;

        /**
         * @brief Performs matrix inversion
         */
        Matrix4 invert() const;

        // Values
        float m11, m12, m13, m14;
        float m21, m22, m23, m24;
        float m31, m32, m33, m34;
        float m41, m42, m43, m44;

        /**
         * @brief Create a translation, rotation and scale matrix
         */
        static Matrix4 trs(Vector3 position, Vector3 rotation, Vector3 scale);

        static Matrix4 identity;

};

std::ostream &operator<<(std::ostream &stream, const Matrix4 &vec);

}
