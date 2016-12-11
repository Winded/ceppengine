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
    UNUSED_PARAM(argc);
    UNUSED_PARAM(argv);

    Vector3 vec(1, 1, 1);
    std::cout << vec.length() << std::endl;

    Matrix4 mat = Matrix4::trs(Vector3(1, 0, 0), Vector3(0, 0, 90), Vector3::one);
    std::cout << mat << std::endl;

    //std::cout << "Ref test begin" << std::endl;
    //testRefs();
    //std::cout << "Ref test complete" << std::endl;

    Engine engine;
    auto runtimeMod = new WindowsRuntimeModule();
    runtimeMod->proc = WindowProc;
    engine.addModule(runtimeMod);
    engine.addModule(new WindowsInputModule());
    engine.addModule(new WindowsFileModule());
    engine.addModule(new GLESRenderModule());
    engine.addModule(new OpenALModule());
    engine.assetLoader()->loadDefaultImporters();

    AudioClip *clip = (AudioClip*)engine.assetLoader()->loadAsset("/memes.wav", "AudioClip");
    Sprite *grassSprite = (Sprite*)engine.assetLoader()->loadAsset("/grass.sprite", "Sprite");
    Sprite *treeSprite = (Sprite*)engine.assetLoader()->loadAsset("/tree.sprite", "Sprite");
    SpriteAnimation *anim = (SpriteAnimation*)engine.assetLoader()->loadAsset("/testanim.spriteanim", "SpriteAnimation");
    Font *font = (Font*)engine.assetLoader()->loadAsset("/LCDSolid.ttf", "Font");

    Scene *scene = new Scene();

    GameObject *go = new GameObject("TestSprite");
    SpriteRenderer *r = (SpriteRenderer*)go->addComponent(new SpriteRenderer());
    r->setSprite(grassSprite);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3(0, 0, 0));
    go->addComponent(new AimAtCursor());

    go = new GameObject("TestSprite");
    r = (SpriteRenderer*)go->addComponent(new SpriteRenderer());
    r->setSprite(treeSprite);
    SpriteAnimator *animator = (SpriteAnimator*)go->addComponent(new SpriteAnimator());
    animator->setAnimation(anim);
    animator->setAutoPlay(true);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3(1, 0, 0));

    go = new GameObject("AudioMedic");
    AudioSource *as = (AudioSource*)go->addComponent(new AudioSource());
    as->setClip(clip);
    go->addComponent(new PlayOnPress());
    go->setParent(scene->rootObject());
    go->setPosition(Vector3::zero);

    go = new GameObject("Txt");
    UIText *uiTxt = (UIText*)go->addComponent(new UIText());
    uiTxt->setFont(font);
    uiTxt->setText("Sample text");
    uiTxt->setFontSize(120);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3(100, 0, 0));

    GameObject *cameraObj = new GameObject("Camera");
    Camera *c = (Camera*)cameraObj->addComponent(new Camera());
    c->setBackgroundColor(Color(100, 100, 100, 255));
    //cameraObj->addComponent(new FPSPrint());
    cameraObj->setParent(scene->rootObject());
    cameraObj->setPosition(Vector3(0, 0, -5.f));

    Engine::instance()->runtimeModule()->setScreenResolution(Vector3(1280, 720, 0));

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
