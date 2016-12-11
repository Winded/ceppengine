#include <iostream>
#include <ctime>
#include <ceppengine/math/vector3.h>
#include <ceppengine/math/matrix4.h>
#include <ceppengine/engine.h>
#include <ceppengine/modules/windows/winruntimemodule.h>
#include <ceppengine/modules/windows/windowsinputmodule.h>
#include <ceppengine/modules/windows/windowsfilemodule.h>
#include <ceppengine/modules/gles/glesrendermodule.h>
#include <ceppengine/modules/audio/openalaudiomodule.h>
#include <ceppengine/gameobject.h>
#include <ceppengine/scene.h>
#include <ceppengine/util/ref.h>
#include <ceppengine/components/rendering/spriterenderer.h>
#include <ceppengine/components/rendering/meshrenderer.h>
#include <ceppengine/components/animation/spriteanimator.h>
#include <ceppengine/components/audio/audiosource.h>
#include <ceppengine/components/ui/uitext.h>
#include <ceppengine/assets/audioclip.h>
#include "components/fpsprint.h"
#include "components/rotator.h"
#include "components/aimatcursor.h"
#include "components/playonpress.h"

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
        ScreenToClient(hWnd, &point);
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

void loadScene(Scene *scene)
{
    GameObject *go = 0;

    GameObject *cameraObj = new GameObject("Camera");
    Camera *c = (Camera*)cameraObj->addComponent(new Camera());
    c->setBackgroundColor(Color::black);
    cameraObj->setParent(scene->rootObject());
    cameraObj->setPosition(Vector3(0, 0, -5.f));

    go = new GameObject("Music");
    AudioSource *as = (AudioSource*)go->addComponent(new AudioSource());
    as->setClip((AudioClip*)Engine::instance()->assetLoader()->loadAsset("/orbital_colossus.wav", "AudioClip"));
    as->setPlayOnStart(true);
    as->setLoop(true);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3::zero);

    go = new GameObject("Background");
    SpriteRenderer *r = (SpriteRenderer*)go->addComponent(new SpriteRenderer());
    r->setSprite((Sprite*)Engine::instance()->assetLoader()->loadAsset("/background.sprite", "Sprite"));
    r->setColor(Color::white);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3::zero);
}

int main(int argc, char *argv[])
{
    UNUSED_PARAM(argc);
    UNUSED_PARAM(argv);

    Engine engine;
    WindowsRuntimeModule *runtimeMod = new WindowsRuntimeModule();
    runtimeMod->proc = WindowProc;
    engine.addModule(runtimeMod);
    engine.addModule(new WindowsInputModule());
    engine.addModule(new WindowsFileModule());
    engine.addModule(new GLESRenderModule());
    engine.addModule(new OpenALModule());
    engine.assetLoader()->loadDefaultImporters();

    Scene *scene = new Scene();

    loadScene(scene);

    Engine::instance()->runtimeModule()->setScreenResolution(Vector3(720, 720, 0));
    Engine::instance()->runtimeModule()->setWindowTitle(L"CeppEngine demo");

    engine.loadScene(scene);

    clock_t timer = clock();

    engine.start();
    while(engine.isRunning()) {
        clock_t currentTime = clock();
        float deltaTime = (float)(currentTime - timer) / (float)CLOCKS_PER_SEC;
        deltaTime = deltaTime * runtimeMod->timeScale();
        timer = currentTime;
        engine.update(deltaTime);
    }

    return 0;
}
