#include <iostream>
#include <ctime>
#include <ceppengine/math/vector3.h>
#include <ceppengine/math/matrix4.h>
#include <ceppengine/engine.h>
#include <ceppengine/modules/windows/winruntimemodule.h>
#include <ceppengine/modules/windows/windowsinputmodule.h>
#include <ceppengine/modules/gles/glesrendermodule.h>
#include <ceppengine/gameobject.h>
#include <ceppengine/scene.h>
#include <ceppengine/util/ref.h>

using namespace cepp;

LRESULT WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT  lRet = 1;

    switch (uMsg)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
    {
        WindowsRuntimeModule *runtimeModule = (WindowsRuntimeModule*)Engine::instance()->runtimeModule();
        GLESRenderModule *renderModule = (GLESRenderModule*)Engine::instance()->renderModule();

        renderModule->render();

        ValidateRect(runtimeModule->getWindowHandle(), NULL);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
    {
        int key = GET_KEYSTATE_WPARAM(wParam);
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setKeyDown(key);
    }
    break;

    case WM_KEYUP:
    {
        int key = GET_KEYSTATE_WPARAM(wParam);
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setKeyUp(key);
    }
    break;

    case WM_MOUSEMOVE:
    {
        POINT point;
        GetCursorPos(&point);
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->updateMousePosition(point);
    }
    break;

    case WM_MOUSEWHEEL:
    {
        float delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->updateMouseDelta(delta);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setMouseButtonDown(0);
    }
    break;
    case WM_LBUTTONUP:
    {
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setMouseButtonUp(0);
    }
    break;
    case WM_RBUTTONDOWN:
    {
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setMouseButtonDown(1);
    }
    break;
    case WM_RBUTTONUP:
    {
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setMouseButtonUp(1);
    }
    break;
    case WM_MBUTTONDOWN:
    {
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setMouseButtonDown(2);
    }
    break;
    case WM_MBUTTONUP:
    {
        WindowsInputModule *module = (WindowsInputModule*)Engine::instance()->inputModule();
        module->setMouseButtonUp(2);
    }
    break;

    default:
        lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;
    }

    return lRet;
}

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

Mesh *testMesh = 0;
Material *testMaterial = 0;

void renderCallback(Object *object, IRenderer *renderer) {
    renderer->setMesh(testMesh);
    renderer->setMaterial(testMaterial);
    renderer->applySettings();
    renderer->draw();
}

void testRendering() {
    testMesh = new Mesh(new float[] {
        -0.5f, 0.5f, 0,
        0.5f, 0.5f, 0,
        0.5f, -0.5f, 0,
        -0.5f, -0.5f, 0
    }, 4 * 3, new float[] {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    }, 4 * 2, new int[] {
        0, 1, 3,
        1, 2, 3
    }, 6);

    Texture *texture = new Texture(1, 1, new char[] {(char)255, (char)255, (char)255, (char)255});
    Shader *shader = new Shader(
                "precision mediump float;                                                                     \
                attribute vec3 position;                                                                      \
                attribute vec2 uvCoordinates;                                                                 \
                                                                                                              \
                varying vec2 UV;                                                                              \
                                                                                                              \
                uniform mat4 WorldToViewportMatrix;                                                           \
                uniform mat4 LocalToWorldMatrix;                                                              \
                                                                                                              \
                void main()                                                                                   \
                {                                                                                             \
                    gl_Position = WorldToViewportMatrix * LocalToWorldMatrix * vec4(position.xyz, 1.0);       \
                    UV = uvCoordinates;                                                                       \
                }",
                "precision mediump float;                                                                     \
                varying vec2 UV;                                                                              \
                                                                                                              \
                uniform sampler2D Texture1;                                                                   \
                uniform vec4 BaseColor;                                                                       \
                                                                                                              \
                void main()                                                                                   \
                {                                                                                             \
                    gl_FragColor = texture2D(Texture1, UV) * BaseColor;                                       \
                }"
                );
    testMaterial = new Material();
    testMaterial->setShader(shader);
    testMaterial->setTexture(texture);

    Matrix4 id = Matrix4::identity;
    float matIdentity[] = {
        id.m11, id.m12, id.m13, id.m14,
        id.m21, id.m22, id.m23, id.m24,
        id.m31, id.m32, id.m33, id.m34,
        id.m41, id.m42, id.m43, id.m44
    };
    float color[] = {1.f, 1.f, 1.f, 1.f};
    Engine::instance()->renderModule()->setGlobalShaderParam("WorldToViewportMatrix", matIdentity, 4 * 4);
    Engine::instance()->renderModule()->setGlobalShaderParam("LocalToWorldMatrix", matIdentity, 4 * 4);
    Engine::instance()->renderModule()->setGlobalShaderParam("BaseColor", color, 4);

    Engine::instance()->renderModule()->addHandler(Engine::instance()->scene(), renderCallback);
}

int main(int argc, char *argv[])
{
    Vector3 vec(1, 1, 1);
    std::cout << vec.length() << std::endl;

    Angle ang;
    std::cout << ang << std::endl;

    Matrix4 mat = Matrix4::trs(Vector3(1, 0, 0), Vector3(0, 0, 90), Vector3::one);
    std::cout << mat << std::endl;

    std::cout << "Ref test begin" << std::endl;
    testRefs();
    std::cout << "Ref test complete" << std::endl;

    Engine engine;
    auto runtimeMod = new WindowsRuntimeModule();
    runtimeMod->proc = WindowProc;
    engine.addModule(runtimeMod);
    engine.addModule(new WindowsInputModule());
    engine.addModule(new GLESRenderModule());

    Scene *scene = new Scene();
    engine.loadScene(scene);

    clock_t timer = clock();

    engine.start();
    testRendering();
    while(engine.isRunning()) {
        clock_t currentTime = clock();
        float deltaTime = (float)(currentTime - timer) / (float)CLOCKS_PER_SEC;
        deltaTime = deltaTime * runtimeMod->timeScale();
        timer = currentTime;
        engine.update(deltaTime);
    }

    return 0;
}
