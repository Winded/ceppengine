#include "matrix4.h"
#include "math.h"
#include <string>
#include <iostream>

namespace cepp {

Matrix4::Matrix4()
{
}

Matrix4::Matrix4(float values[])
{
    m11 = values[0];
    m12 = values[1];
    m13 = values[2];
    m14 = values[3];
    m21 = values[4];
    m22 = values[5];
    m23 = values[6];
    m24 = values[7];
    m31 = values[8];
    m32 = values[9];
    m33 = values[10];
    m34 = values[11];
    m41 = values[12];
    m42 = values[13];
    m43 = values[14];
    m44 = values[15];
}

Matrix4 Matrix4::operator*(const Matrix4 &mat) const
{
    return multiply(mat);
}

float Matrix4::determinant() const
{
    return m11 * (m22*(m33*m44 - m43*m34) - m23*(m32*m44 - m42*m34) + m24*(m32*m43 - m42*m33))
            - m12 * (m21*(m33*m44 - m43*m34) - m23*(m31*m44 - m41*m34) + m24*(m31*m43 - m41*m33))
            + m13 * (m21*(m32*m44 - m42*m34) - m22*(m31*m44 - m41*m34) + m24 *(m31*m42 - m41*m32))
            - m14 * (m21*(m32*m43 - m42*m33) - m22*(m31*m43 - m41*m33) + m23 *(m31*m42 - m41*m32));
}

Matrix4 Matrix4::multiply(const Matrix4 &mat) const
{
    Matrix4 result;

    result.m11 = m11*mat.m11+m12*mat.m21+m13*mat.m31+m14*mat.m41;
    result.m12 = m11*mat.m12+m12*mat.m22+m13*mat.m32+m14*mat.m42;
    result.m13 = m11*mat.m13+m12*mat.m23+m13*mat.m33+m14*mat.m43;
    result.m14 = m11*mat.m14+m12*mat.m24+m13*mat.m34+m14*mat.m44;

    result.m21 = m21*mat.m11+m22*mat.m21+m23*mat.m31+m24*mat.m41;
    result.m22 = m21*mat.m12+m22*mat.m22+m23*mat.m32+m24*mat.m42;
    result.m23 = m21*mat.m13+m22*mat.m23+m23*mat.m33+m24*mat.m43;
    result.m24 = m21*mat.m14+m22*mat.m24+m23*mat.m34+m24*mat.m44;

    result.m31 = m31*mat.m11+m32*mat.m21+m33*mat.m31+m34*mat.m41;
    result.m32 = m31*mat.m12+m32*mat.m22+m33*mat.m32+m34*mat.m42;
    result.m33 = m31*mat.m13+m32*mat.m23+m33*mat.m33+m34*mat.m43;
    result.m34 = m31*mat.m14+m32*mat.m24+m33*mat.m34+m34*mat.m44;

    result.m41 = m41*mat.m11+m42*mat.m21+m43*mat.m31+m44*mat.m41;
    result.m42 = m41*mat.m12+m42*mat.m22+m43*mat.m32+m44*mat.m42;
    result.m43 = m41*mat.m13+m42*mat.m23+m43*mat.m33+m44*mat.m43;
    result.m44 = m41*mat.m14+m42*mat.m24+m43*mat.m34+m44*mat.m44;

    return result;
}

Matrix4 Matrix4::invert() const
{
    Matrix4 result;

    result.m11 = m22*m33*m44+m23*m34*m42+m24*m32*m43-m22*m34*m43-m23*m32*m44-m24*m33*m42;
    result.m12 = m12*m34*m43+m13*m32*m44+m14*m33*m42-m12*m33*m44-m13*m34*m42-m14*m32*m43;
    result.m13 = m12*m23*m44+m13*m24*m42+m14*m22*m43-m12*m24*m43-m13*m22*m44-m14*m23*m42;
    result.m14 = m12*m24*m33+m13*m22*m34+m14*m23*m32-m12*m23*m34-m13*m24*m32-m14*m22*m33;

    result.m21 = m21*m34*m43+m23*m31*m44+m24*m33*m41-m21*m33*m44-m23*m34*m41-m24*m31*m43;
    result.m22 = m11*m33*m44+m13*m34*m41+m14*m31*m43-m11*m34*m43-m13*m31*m44-m14*m33*m41;
    result.m23 = -1*(m11*m23*m44-m13*m21*m44+m14*m21*m43-m11*m24*m43+m13*m41*m24-m14*m23*m41);
    result.m24 = m11*m23*m34+m13*m24*m31+m14*m21*m33-m11*m24*m33-m13*m21*m34-m14*m23*m31;

    result.m31 = m21*m32*m44+m22*m34*m41+m24*m31*m42-m21*m34*m42-m22*m31*m44-m24*m32*m41;
    result.m32 = m11*m34*m42+m12*m31*m44+m14*m32*m41-m11*m32*m44-m12*m34*m41-m14*m31*m42;
    result.m33 = m11*m22*m44+m12*m24*m41+m14*m21*m42-m11*m24*m42-m12*m21*m44-m14*m22*m41;
    result.m34 = m11*m24*m32+m12*m21*m34+m14*m22*m31-m11*m22*m34-m12*m24*m31-m14*m21*m32;

    result.m41 = m21*m33*m42+m22*m31*m43+m23*m32*m41-m21*m32*m43-m22*m33*m41-m23*m31*m42;
    result.m42 = m11*m32*m43+m12*m33*m41+m13*m31*m42-m11*m33*m42-m12*m31*m43-m13*m32*m41;
    result.m43 = m11*m23*m42+m12*m21*m43+m13*m22*m41-m11*m22*m43-m12*m23*m41-m13*m21*m42;
    result.m44 = m11*m22*m33+m12*m23*m31+m13*m21*m32-m11*m23*m32-m12*m21*m33-m13*m22*m31;

    float det = determinant();
    result.m11 /= det;
    result.m21 /= det;
    result.m31 /= det;
    result.m41 /= det;
    result.m12 /= det;
    result.m22 /= det;
    result.m32 /= det;
    result.m42 /= det;
    result.m13 /= det;
    result.m23 /= det;
    result.m33 /= det;
    result.m43 /= det;
    result.m14 /= det;
    result.m24 /= det;
    result.m34 /= det;
    result.m44 /= det;

    return result;
}

float *Matrix4::toArray() const
{
    return new float[16] {
        m11, m12, m13, m14,
        m21, m22, m23, m24,
        m31, m32, m33, m34,
        m41, m42, m43, m44
    };
}

float *Matrix4::toColumnMajorArray() const
{
    return new float[16] {
        m11, m21, m31, m41,
        m12, m22, m32, m42,
        m13, m23, m33, m43,
        m14, m24, m34, m44
    };
}

Matrix4 Matrix4::trs(Vector3 position, Vector3 rotation, Vector3 scale)
{
    // Transformation matrix
    Matrix4 tMatrix = Matrix4::identity;
    tMatrix.m14 = position.x;
    tMatrix.m24 = position.y;
    tMatrix.m34 = position.z;

    Matrix4 sMatrix = Matrix4::identity;
    sMatrix.m11 = scale.x;
    sMatrix.m22 = scale.y;
    sMatrix.m33 = scale.z;

    // Create rotation matrices

    Matrix4 xMatrix = Matrix4::identity;
    xMatrix.m22 = Math::cos(rotation.x * Math::deg2rad);
    xMatrix.m23 = -Math::sin(rotation.x * Math::deg2rad);
    xMatrix.m32 = Math::sin(rotation.x * Math::deg2rad);
    xMatrix.m33 = Math::cos(rotation.x * Math::deg2rad);

    Matrix4 yMatrix = Matrix4::identity;
    yMatrix.m11 = Math::cos(rotation.y * Math::deg2rad);
    yMatrix.m31 = -Math::sin(rotation.y * Math::deg2rad);
    yMatrix.m13 = Math::sin(rotation.y * Math::deg2rad);
    yMatrix.m33 = Math::cos(rotation.y * Math::deg2rad);

    Matrix4 zMatrix = Matrix4::identity;
    zMatrix.m11 = Math::cos(rotation.z * Math::deg2rad);
    zMatrix.m12 = -Math::sin(rotation.z * Math::deg2rad);
    zMatrix.m21 = Math::sin(rotation.z * Math::deg2rad);
    zMatrix.m22 = Math::cos(rotation.z * Math::deg2rad);

    Matrix4 rMatrix = xMatrix * yMatrix * zMatrix;

    // Mulitply
    return sMatrix * tMatrix * rMatrix;
}

Matrix4 Matrix4::identity(new float[16] {
                            1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1,
                          });

std::ostream &operator<<(std::ostream &stream, const Matrix4 &m)
{
    stream << "[" << std::to_string(m.m11) << ", " << std::to_string(m.m12) << ", "
           << std::to_string(m.m13) << ", " << std::to_string(m.m14) << "]" << std::endl;
    stream << "[" << std::to_string(m.m21) << ", " << std::to_string(m.m22) << ", "
           << std::to_string(m.m23) << ", " << std::to_string(m.m24) << "]" << std::endl;
    stream << "[" << std::to_string(m.m31) << ", " << std::to_string(m.m32) << ", "
           << std::to_string(m.m33) << ", " << std::to_string(m.m34) << "]" << std::endl;
    stream << "[" << std::to_string(m.m41) << ", " << std::to_string(m.m42) << ", "
           << std::to_string(m.m43) << ", " << std::to_string(m.m44) << "]" << std::endl;
    return stream;
}

}

