#include "glesrendermodule.h"
#include "../../engine.h"
#include "../windows/winruntimemodule.h"
#include <GLES2/gl2.h>
#include <iostream>
#include <algorithm>

namespace cepp {

GLESRenderer::GLESRenderer() : module(0), mMaterial(0), mMesh(0)
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader *shader = mMaterial ? mMaterial->shader() : Engine::instance()->defaultAssets()->basicShader();
    int shaderProgram = shader->load();
    glUseProgram(shaderProgram);

    GLenum err = glGetError();
    assert(err == GL_FALSE);

    Texture *texture = mMaterial ? mMaterial->texture() : Engine::instance()->defaultAssets()->whiteTexture();
    glBindTexture(GL_TEXTURE_2D, texture->load());

    err = glGetError();
    assert(err == GL_FALSE);

    applyShaderParams(shaderProgram, module->mShaderParams);
    if(mMaterial)
        applyShaderParams(shaderProgram, mMaterial->shaderParameters());

    err = glGetError();
    assert(err == GL_FALSE);
}

void GLESRenderer::draw()
{
    if(!mMesh)
        return;

    int id = mMesh->load();
    auto mIt = std::find_if(module->mModels.begin(), module->mModels.end(), [id](const GLESModel &model) {
       return model.VBO == id;
    });
    assert(mIt != module->mModels.end());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*mIt).EBO);
    glBindBuffer(GL_ARRAY_BUFFER, (*mIt).VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLE_STRIP, mMesh->elementBufferLength(), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLenum err = glGetError();
    assert(err == GL_FALSE);
}

void GLESRenderer::clear(Color color)
{
    float r = (float)color.r / 255.f;
    float g = (float)color.g / 255.f;
    float b = (float)color.b / 255.f;
    float a = (float)color.a / 255.f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, a);

    GLenum err = glGetError();
    assert(err == GL_FALSE);
}

void GLESRenderer::applyShaderParams(int program, const std::vector<ShaderParameter> &params)
{
    for(auto it = params.begin(); it != params.end(); ++it) {
        const ShaderParameter &param = *it;
        int location = glGetUniformLocation(program, param.name.c_str());
        if(location == -1 || !param.data)
            continue;

        switch(param.size) {
        case 1:
            glUniform1fv(location, 1, param.data);
            break;
        case 2:
            glUniform2fv(location, 1, param.data);
            break;
        case 3:
            glUniform3fv(location, 1, param.data);
            break;
        case 4:
            glUniform4fv(location, 1, param.data);
            break;
        case 4 * 4:
            glUniformMatrix4fv(location, 1, GL_FALSE, param.data);
            break;
        default:
            assert("Unsupported param size" && 0);
            break;
        }

        GLenum err = glGetError();
        assert(err == GL_FALSE);
    }
}

GLESRenderModule::GLESRenderModule()
    : mInitialized(false), mVSync(false), mNativeWindow(0), mNativeDisplay(0), mEGLDisplay(0), mEGLContext(0), mEGLSurface(0)
{
    mRenderer.module = this;
}

bool GLESRenderModule::vsync() const
{
    return mVSync;
}

void GLESRenderModule::setVSync(bool vsync)
{
    mVSync = vsync;
    if(mEGLDisplay) {
        eglSwapInterval(mEGLDisplay, mVSync ? 1 : 0);
    }
}

void GLESRenderModule::addHandler(Object *object, RenderModule::Callback function)
{
    GLESRenderCallback cb;
    cb.object = object;
    cb.callback = function;
    mHandlers.push_back(cb);
}

void GLESRenderModule::removeHandler(Object *object)
{
    auto it = std::find_if(mHandlers.begin(), mHandlers.end(), [object](const GLESRenderCallback &cb) {
        return cb.object == object;
    });
    if(it != mHandlers.end()) {
        it = mHandlers.erase(it);
    }
}

int GLESRenderModule::createShader(Shader *shader)
{
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    const char *source = shader->vertexShaderSource();
    int length = shader->vertexShaderSourceLength();
    glShaderSource(vertex, 1, &source, &length);
    glCompileShader(vertex);

    char log[2048];
    glGetShaderInfoLog(vertex, 2048, &length, log);
    if(length > 0) {
        std::cout << log << std::endl;
    }

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    source = shader->fragmentShaderSource();
    length = shader->fragmentShaderSourceLength();
    glShaderSource(fragment, 1, &source, &length);
    glCompileShader(fragment);

    glGetShaderInfoLog(fragment, 2048, &length, log);
    if(length > 0) {
        std::cout << log << std::endl;
    }

    GLuint p = glCreateProgram();
    glAttachShader(p, vertex);
    glAttachShader(p, fragment);
    glLinkProgram(p);

    glGetProgramInfoLog(p, 2048, &length, log);
    if(length > 0) {
        std::cout << log << std::endl;
    }

    return p;
}

void GLESRenderModule::updateShader(int handle, Shader *shader)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(shader);
    assert("Not implemented" && 0);
}

void GLESRenderModule::deleteShader(int handle)
{
    glDeleteProgram(handle);
}

int GLESRenderModule::createModel(Mesh *mesh)
{
    float *vBuf = mesh->vertexBuffer();
    int vBufLength = mesh->vertexBufferLength();
    int *eBuf = mesh->elementBuffer();
    int eBufLength = mesh->elementBufferLength();

    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vBufLength * sizeof(float), vBuf, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eBufLength * sizeof(int), eBuf, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mModels.push_back(GLESModel(vbo, ebo));

    GLenum err = glGetError();
    assert(err == GL_FALSE);

    return vbo;
}

void GLESRenderModule::updateModel(int handle, Mesh *mesh)
{
    auto it = std::find_if(mModels.begin(), mModels.end(), [handle](const GLESModel &model) {
       return model.VBO == handle;
    });
    if(it != mModels.end()) {
        float *vBuf = mesh->vertexBuffer();
        int vBufLength = mesh->vertexBufferLength();
        int *eBuf = mesh->elementBuffer();
        int eBufLength = mesh->elementBufferLength();
        GLuint vbo = (*it).VBO;
        GLuint ebo = (*it).EBO;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vBufLength * sizeof(float), vBuf, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, eBufLength * sizeof(int), eBuf, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        GLenum err = glGetError();
        assert(err == GL_FALSE);
    }
}

void GLESRenderModule::deleteModel(int handle)
{
    auto it = std::find_if(mModels.begin(), mModels.end(), [handle](const GLESModel &model) {
       return model.VBO == handle;
    });
    if(it != mModels.end()) {
        glDeleteBuffers(1, &((*it).VBO));
        glDeleteBuffers(1, &((*it).EBO));
        it = mModels.erase(it);
    }
}

int GLESRenderModule::createTexture(Texture *texture)
{
    GLuint glTex = 0;
    glGenTextures(1, &glTex);
    glBindTexture(GL_TEXTURE_2D, glTex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width(), texture->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data());

    GLenum err = glGetError();
    if(err != GL_FALSE) {
        std::cout << "GLES texture error! " << err << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    return glTex;
}

void GLESRenderModule::updateTexture(int handle, Texture *texture, bool greyscale)
{
    glBindTexture(GL_TEXTURE_2D, handle);
    if(greyscale) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texture->width(), texture->height(), 0, GL_ALPHA, GL_UNSIGNED_BYTE, texture->data());
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width(), texture->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data());
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err = glGetError();
    assert(err == GL_FALSE);
}

void GLESRenderModule::deleteTexture(int handle)
{
    GLuint h = handle;
    glDeleteTextures(1, &h);
}

float *GLESRenderModule::getGlobalShaderParam(const std::string &name, int *size) const
{
    auto it = std::find_if(mShaderParams.begin(), mShaderParams.end(), [name](const ShaderParameter &param) {
       return param.name == name;
    });

    if(it != mShaderParams.end()) {
        *size = (*it).size;
        return (*it).data;
    }

    return 0;
}

void GLESRenderModule::setGlobalShaderParam(const std::string &name, float *value, int size)
{
    auto it = std::find_if(mShaderParams.begin(), mShaderParams.end(), [name](const ShaderParameter &param) {
       return param.name == name;
    });

    if(it != mShaderParams.end()) {
        // Parameter exists, but is different size; do realloc
        if(size != (*it).size)
            realloc((*it).data, size * sizeof(float));
        memcpy((*it).data, value, size * sizeof(float));
        (*it).size = size;
    }
    else {
        // Create new parameter
        float *data = new float[size];
        memcpy(data, value, size * sizeof(float));
        ShaderParameter param;
        param.data = data;
        param.size = size;
        param.name = name;
        mShaderParams.push_back(param);
    }
}

void GLESRenderModule::deleteGlobalShaderParam(const std::string &name)
{
    auto it = std::find_if(mShaderParams.begin(), mShaderParams.end(), [name](const ShaderParameter &param) {
       return param.name == name;
    });

    if(it != mShaderParams.end()) {
        delete (*it).data;
        it = mShaderParams.erase(it);
    }
}

void GLESRenderModule::initialize()
{
    RenderModule::initialize();

    // Windows code
    WindowsRuntimeModule *runtimeMod = (WindowsRuntimeModule*)Engine::instance()->runtimeModule();
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

    // Update swap interval
    setVSync(mVSync);

    mInitialized = true;
}

void GLESRenderModule::render()
{
    if(!mInitialized) return;

    Camera *camera = Engine::instance()->scene()->mainCamera();

    if(camera) {
        mRenderer.clear(camera->backgroundColor());

        float *viewMat = camera->worldToViewportMatrix().toColumnMajorArray();
        setGlobalShaderParam("WorldToViewportMatrix", viewMat, 4 * 4);
        delete viewMat;

        for(auto it = mHandlers.begin(); it != mHandlers.end(); ++it) {
            (*it).callback((*it).object, (IRenderer*)(&mRenderer));
        }
    }
    else {
        mRenderer.clear(Color::black);
    }

    eglSwapBuffers(mEGLDisplay, mEGLSurface);
}

} // namespace cepp
