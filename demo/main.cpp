#include <iostream>
#include <ceppengine/math/vector3.h>
#include <ceppengine/math/matrix4.h>
#include <ceppengine/engine.h>
#include <ceppengine/gameobject.h>
#include <ceppengine/scene.h>
#include <ceppengine/util/ref.h>

using namespace cepp;

void testRefs() {
    Ref<GameObject> go = new GameObject("Test");
    {
        Ref<GameObject> go2 = go;
    }
    GameObject *go3 = go;
    std::cout << go3->name() << std::endl;

    std::vector<Ref<GameObject>> goList;
    for(int i = 0; i < 1000; i++)
        goList.push_back(new GameObject("Test" + std::to_string(i)));
    for(auto it = goList.begin(); it != goList.end(); ++it) {
        GameObject *go4 = *it;
    }
}

int main(int argc, char *argv[])
{
    Vector3 vec(1, 1, 1);
    std::cout << vec.length() << std::endl;

    Angle ang;
    std::cout << ang << std::endl;

    Matrix4 mat = Matrix4::trs(Vector3(1, 0, 0), Angle(0, 0, 90), Vector3::one);
    std::cout << mat << std::endl;

    std::cout << "Ref test begin" << std::endl;
    testRefs();
    std::cout << "Ref test complete" << std::endl;

    Engine engine;

    Scene *scene = new Scene();
    engine.loadScene(scene);

    engine.start();
    while(engine.isRunning()) {
        engine.update(1.0f);
    }

    return 0;
}
