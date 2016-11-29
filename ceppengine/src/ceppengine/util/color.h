#ifndef FCOLOR_H
#define FCOLOR_H

#include <inttypes.h>

namespace cepp {

/**
 * Represents an RGB color with alpha channel.
 */
class Color
{
    public:
        Color();
        Color(int pR, int pG, int pB);
        Color(int pR, int pG, int pB, int pA);

        /**
         * Create a float array of normalized color values (0 to 1)
         */
        float *toNormalizedArray() const;

        // Values
        uint8_t r, g, b, a;

        // Static defaults
        static Color black;
        static Color white;
        static Color red;
        static Color green;
        static Color blue;
};

}

#endif // FCOLOR_H
