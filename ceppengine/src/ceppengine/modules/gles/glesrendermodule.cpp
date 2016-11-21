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
    Shader *shader = mMaterial ? mMaterial->shader() : Engine::instance()->defaultAssets()->basicShader();
    int shaderProgram = shader->load();
    glUseProgram(shaderProgram);

    Texture *texture = mMaterial ? mMaterial->texture() : Engine::instance()->defaultAssets()->whiteTexture();
    glBindTexture(GL_TEXTURE_2D, texture->load());

    applyShaderParams(shaderProgram, module->mShaderParams);
    if(mMaterial)
        applyShaderParams(shaderProgram, mMaterial->shaderParameters());
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

    glBindBuffer(GL_ARRAY_BUFFER, (*mIt).VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*mIt).EBO);
    glDrawElements(GL_TRIANGLES, mMesh->indicesLength(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLESRenderer::clear(Color color)
{
    float r = (float)color.r / 255.f;
    float g = (float)color.g / 255.f;
    float b = (float)color.b / 255.f;
    float a = (float)color.a / 255.f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, a);
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
{
    mRenderer.module = this;
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
    int bufLength = 0;
    float *buffer = combineArraysToBuffer(mesh->vertices(), mesh->verticesLength(), mesh->uvCoordinates(), mesh->uvCoordinatesLength(), &bufLength);
    int *elements = mesh->indices();
    int elementsLength = mesh->indicesLength();

    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, bufLength * sizeof(float), buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsLength * sizeof(int), elements, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mModels.push_back(GLESModel(vbo, ebo));

    return vbo;
}

void GLESRenderModule::updateModel(int handle, Mesh *mesh)
{
    auto it = std::find_if(mModels.begin(), mModels.end(), [handle](const GLESModel &model) {
       return model.VBO == handle;
    });
    if(it != mModels.end()) {
        int bufLength = 0;
        float *buffer = combineArraysToBuffer(mesh->vertices(), mesh->verticesLength(), mesh->uvCoordinates(), mesh->uvCoordinatesLength(), &bufLength);
        int *elements = mesh->indices();
        int elementsLength = mesh->indicesLength();
        GLuint vbo = (*it).VBO;
        GLuint ebo = (*it).EBO;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, bufLength * sizeof(float), buffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsLength * sizeof(int), elements, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

void GLESRenderModule::updateTexture(int handle, Texture *texture)
{
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->width(), texture->height(), GL_RGBA, GL_UNSIGNED_BYTE, texture->data());
    glBindTexture(GL_TEXTURE_2D, 0);
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
    // Copy data first
    float *data = new float[size];
    for(int i = 0; i < size; i++)
        data[i] = value[i];

    auto it = std::find_if(mShaderParams.begin(), mShaderParams.end(), [name](const ShaderParameter &param) {
       return param.name == name;
    });

    if(it != mShaderParams.end()) {
        delete (*it).data;
        (*it).data = data;
        (*it).size = size;
    }
    else {
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
}

void GLESRenderModule::render()
{
    Camera *camera = Engine::instance()->scene()->mainCamera();

    if(camera) {
        mRenderer.clear(camera->backgroundColor());

        float *viewMat = camera->worldToViewportMatrix().toArray();
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

float *GLESRenderModule::combineArraysToBuffer(float *vertices, int vertexLength, float *uvCoords, int uvCoordsLength, int *length)
{
    int len = vertexLength + uvCoordsLength;
    float *buf = new float[len];

    int idx = 0;
    int vIdx = 0;
    int uIdx = 0;
    while(true) {
        if(idx > len - 5)
            break;

        buf[idx] = vertices[vIdx];
        buf[idx + 1] = vertices[vIdx + 1];
        buf[idx + 2] = vertices[vIdx + 2];
        if(uvCoords && uIdx <= uvCoordsLength - 2) {
            buf[idx + 3] = uvCoords[uIdx];
            buf[idx + 4] = uvCoords[uIdx + 1];
        }
        else {
            buf[idx + 3] = 0;
            buf[idx + 4] = 0;
        }

        idx += 5;
        vIdx += 3;
        uIdx += 2;
    }

    *length = len;
    return buf;
}

} // namespace cepp
