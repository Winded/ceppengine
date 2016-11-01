#include <iostream>
#include <ceppengine/math/vector3.h>

using namespace std;

int main(int argc, char *argv[])
{
    cepp::Vector3 vec(1, 1, 1);
    std::cout << vec.length() << std::endl;
    return 0;
}
