#ifndef FMATH_H
#define FMATH_H

#include <math.h>

namespace cepp {

/**
 * @brief Math library, mostly consisting of STD wrappers
 */
class Math
{
    public:

        inline static float sin(float value)
        {
            return ::sin(value);
        }
        inline static float cos(float value)
        {
            return ::cos(value);
        }
        inline static float tan(float value)
        {
            return ::tan(value);
        }

        inline static float asin(float value)
        {
            return ::asin(value);
        }
        inline static float acos(float value)
        {
            return ::acos(value);
        }
        inline static float atan(float value)
        {
            return ::atan(value);
        }

        inline static float atan2(float v1, float v2)
        {
            return ::atan2(v1, v2);
        }

        inline static int abs(int value)
        {
            return value < 0 ? -value : value;
        }

        inline static float abs(float value)
        {
            return ::fabs(value);
        }

        inline static float sqrt(float value)
        {
            return ::sqrt(value);
        }

        inline static float pow(float v1, float v2)
        {
            return ::pow(v1, v2);
        }

        inline static float mod(float v1, float v2)
        {
            return ::fmod(v1, v2);
        }

        inline static float round(float value)
        {
            return ::roundf(value);
        }

        inline static int roundToInt(float value)
        {
            return (int)round(value);
        }

        inline static float floor(float value)
        {
            return ::floorf(value);
        }

        inline static int floorToInt(float value)
        {
            return (int)floor(value);
        }

        inline static float ceil(float value)
        {
            return ::ceilf(value);
        }

        inline static int ceilToInt(float value)
        {
            return (int)ceil(value);
        }

        template<typename T>
        inline static T clamp(T value, T min, T max)
        {
            if(value < min)
                return min;
            else if(value > max)
                return max;
            return value;
        }

        static const float pi;

        static const float deg2rad;
        static const float rad2deg;
};

}


#endif // FMATH_H
