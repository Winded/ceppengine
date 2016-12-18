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
#include "components/playermovement.h"
#include "components/playeranimations.h"
#include "components/score.h"
#include "components/enemyspawner.h"

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
    cameraObj->setPosition(Vector3(0, 2, -5.f));

    go = new GameObject("Music");
    AudioSource *as = (AudioSource*)go->addComponent(new AudioSource());
    as->setClip((AudioClip*)Engine::instance()->assetLoader()->loadAsset("/orbital_colossus.wav", "AudioClip"));
    as->setPlayOnStart(true);
    as->setLoop(true);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3::zero);

    Sprite *background = (Sprite*)Engine::instance()->assetLoader()->loadAsset("/background.sprite", "Sprite");
    go = new GameObject("Background");
    SpriteRenderer *r = (SpriteRenderer*)go->addComponent(new SpriteRenderer());
    r->setSprite(background);
    r->setColor(Color::white);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3(0, 2));

    go = new GameObject("Player");
    r = (SpriteRenderer*)go->addComponent(new SpriteRenderer());
    r->setSprite((Sprite*)Engine::instance()->assetLoader()->loadAsset("/player_idle.sprite", "Sprite"));
    r->setColor(Color::white);
    SpriteAnimator *animator = (SpriteAnimator*)go->addComponent(new SpriteAnimator());
    AudioSource *playerShoot = (AudioSource*)go->addComponent(new AudioSource());
    playerShoot->setClip((AudioClip*)Engine::instance()->assetLoader()->loadAsset("/shoot.wav", "AudioClip"));
    PlayerMovement *pm = (PlayerMovement*)go->addComponent(new PlayerMovement());
    pm->setMinBounds(Vector3(-2, -10));
    pm->setMaxBounds(Vector3(2, 10));
    pm->setSpeed(1);
    PlayerWeapon *pw = (PlayerWeapon*)go->addComponent(new PlayerWeapon());
    pw->setShootKey(' ');
    PlayerAnimations *pa = (PlayerAnimations*)go->addComponent(new PlayerAnimations());
    pa->setIdleAnimation((SpriteAnimation*)Engine::instance()->assetLoader()->loadAsset("/player_idle.spriteanim", "SpriteAnimation"));
    pa->setShootAnimation((SpriteAnimation*)Engine::instance()->assetLoader()->loadAsset("/player_shoot.spriteanim", "SpriteAnimation"));
    go->setParent(scene->rootObject());
    go->setPosition(Vector3::zero);

    go = new GameObject("EnemySpawner");
    EnemySpawner *es = (EnemySpawner*)go->addComponent(new EnemySpawner());
    es->setSpawnFrequency(5.f);
    go->setParent(scene->rootObject());
    go->setPosition(Vector3::zero);

    Vector3 screen = Engine::instance()->runtimeModule()->screenResolution();

    go = new GameObject("Score");
    UIText *uiText = (UIText*)go->addComponent(new UIText());
    uiText->setFont((Font*)Engine::instance()->assetLoader()->loadAsset("/LCDSolid.ttf", "Font"));
    uiText->setFontSize(32);
    uiText->setText("0");
    go->addComponent(new Score());
    go->setParent(scene->rootObject());
    go->setPosition(Vector3(0, screen.y + 80));
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
