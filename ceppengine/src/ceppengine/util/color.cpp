#include "color.h"

namespace cepp {

Color::Color()
    : r((int8_t)0), g((int8_t)0), b((int8_t)0), a((int8_t)255)
{
}

Color::Color(int pR, int pG, int pB)
    : r(pR), g(pG), b(pB), a((int8_t)255)
{
}

Color::Color(int pR, int pG, int pB, int pA)
    : r(pR), g(pG), b(pB), a(pA)
{
}

Color Color::black(0, 0, 0, 255);
Color Color::white(255, 255, 255, 255);
Color Color::red(255, 0, 0, 255);
Color Color::green(0, 255, 0, 255);
Color Color::blue(0, 0, 255, 255);

}
