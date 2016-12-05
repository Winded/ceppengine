#pragma once

#include "../rendermodule.h"
#include "../../util/ref.h"
#include <EGL/egl.h>
#include <EGL/eglplatform.h>
#include "../../assets/material.h"

namespace cepp {

class GLESRenderModule;

struct GLESModel {
        GLESModel(unsigned int vbo, unsigned int ebo) : VBO(vbo), EBO(ebo) {}
        unsigned int VBO, EBO;
};

struct GLESRenderCallback {
        Object *object;
        RenderModule::Callback callback;
};

class GLESRenderer : public IRenderer
{
    public:
        GLESRenderer();

        virtual Material *material() const;
        virtual void setMaterial(Material *material);

        virtual Mesh *mesh() const;
        virtual void setMesh(Mesh *mesh);

        virtual void applySettings();

        virtual void draw();
        virtual void clear(Color color);

        GLESRenderModule *module;

    private:
        void applyShaderParams(int program, const std::vector<ShaderParameter> &params);

        Material *mMaterial;
        Mesh *mMesh;
};

class GLESRenderModule : public RenderModule
{
    public:
        GLESRenderModule();

        virtual void addHandler(Object *object, Callback function);
        virtual void removeHandler(Object *object);

        virtual int createShader(Shader *shader);
        virtual void updateShader(int handle, Shader *shader);
        virtual void deleteShader(int handle);

        virtual int createModel(Mesh *mesh);
        virtual void updateModel(int handle, Mesh *mesh);
        virtual void deleteModel(int handle);

        virtual int createTexture(Texture *texture);
        virtual void updateTexture(int handle, Texture *texture);
        virtual void deleteTexture(int handle);

        virtual float *getGlobalShaderParam(const std::string &name, int *size) const;
        virtual void setGlobalShaderParam(const std::string &name, float *value, int size);
        virtual void deleteGlobalShaderParam(const std::string &name);

        virtual void initialize();

        void render();

    private:
        EGLNativeWindowType mNativeWindow;
        EGLNativeDisplayType mNativeDisplay;
        EGLDisplay mEGLDisplay;
        EGLContext mEGLContext;
        EGLSurface mEGLSurface;

        GLESRenderer mRenderer;

        std::vector<GLESRenderCallback> mHandlers;

        std::vector<GLESModel> mModels;
        std::vector<ShaderParameter> mShaderParams;

        friend class GLESRenderer;
};

} // namespace cepp
