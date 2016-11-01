#include "lrand.h"
#include <cstdlib>
#include <time.h>

long lrand() {
    int r = 1 + (rand() - 1);

    if (sizeof(int) < sizeof(long))
        return (static_cast<long>(rand()) << (sizeof(int) * 8)) |
               r;

    return r;
}

unsigned long ulrand() {
    return (unsigned long)lrand();
}
