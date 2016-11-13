#include "glesrendermodule.h"
#include "../../engine.h"
#include "../windows/winruntimemodule.h"
#include <GLES2/gl2.h>

namespace cepp {

GLESRenderer::GLESRenderer() : mMaterial(0), mMesh(0)
{

}

Material *GLESRenderer::material() const
{
    return mMaterial;
}

void GLESRenderer::setMaterial(Material *material)
{
    mMaterial = material;
}

Mesh *GLESRenderer::mesh() const
{
    return mMesh;
}

void GLESRenderer::setMesh(Mesh *mesh)
{
    mMesh = mesh;
}

void GLESRenderer::applySettings()
{
    // TODO
}

void GLESRenderer::clear(Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void GLESRenderer::draw()
{
    // TODO
}

GLESRenderModule::GLESRenderModule()
{

}

int GLESRenderModule::createShader(Shader *shader)
{
    // TODO
    return 0;
}

void GLESRenderModule::updateShader(int handle, Shader *shader)
{
    // TODO
}

void GLESRenderModule::deleteShader(int handle)
{
    // TODO
}

int GLESRenderModule::createModel(Mesh *mesh)
{
    // TODO
    return 0;
}

void GLESRenderModule::updateModel(int handle, Mesh *mesh)
{
    // TODO
}

void GLESRenderModule::deleteModel(int handle)
{
    // TODO
}

int GLESRenderModule::createTexture(Texture *texture)
{
    // TODO
    return 0;
}

void GLESRenderModule::updateTexture(int handle, Texture *texture)
{
    // TODO
}

void GLESRenderModule::deleteTexture(int handle)
{
    // TODO
}

float *GLESRenderModule::getGlobalShaderParam(const std::string &name, int *size) const
{
    // TODO
    return 0;
}

void GLESRenderModule::setGlobalShaderParam(const std::string &name, float *value, int size)
{
    // TODO
}

void GLESRenderModule::deleteGlobalShaderParam(const std::string &name)
{
    // TODO
}

void GLESRenderModule::initialize()
{
    // Windows code
    WindowsRuntimeModule *runtimeMod = (WindowsRuntimeModule*)Engine::instance()->getModule("RuntimeModule");
    mNativeWindow = runtimeMod->getWindowHandle();
    mNativeDisplay = GetDC(runtimeMod->getWindowHandle());

    assert(mNativeWindow && mNativeDisplay);

    EGLint attribList[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 16,
        EGL_STENCIL_SIZE, EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, 0,
        EGL_NONE
    };

    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLConfig config;
    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

    // Get Display
    mEGLDisplay = eglGetDisplay(mNativeDisplay);
    if (mEGLDisplay == EGL_NO_DISPLAY)
    {
        return;
    }

    // Initialize EGL
    if (!eglInitialize(mEGLDisplay, &majorVersion, &minorVersion))
    {
        return;
    }

    // Get configs
    if (!eglGetConfigs(mEGLDisplay, NULL, 0, &numConfigs))
    {
        return;
    }

    // Choose config
    if (!eglChooseConfig(mEGLDisplay, attribList, &config, 1, &numConfigs))
    {
        return;
    }

    // Create a surface
    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, config, mNativeWindow, NULL);
    if (mEGLSurface == EGL_NO_SURFACE)
    {
        return;
    }

    // Create a GL context
    mEGLContext = eglCreateContext(mEGLDisplay, config, EGL_NO_CONTEXT, contextAttribs);
    if (mEGLContext == EGL_NO_CONTEXT)
    {
        return;
    }

    // Make the context current
    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext))
    {
        return;
    }
}

} // namespace cepp
