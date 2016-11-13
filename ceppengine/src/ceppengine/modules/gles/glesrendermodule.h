#pragma once

#include "../rendermodule.h"
#include "../../util/ref.h"
#include "EGL/egl.h"
#include "EGL/eglplatform.h"

namespace cepp {

class GLESRenderer : IRenderer
{
    public:
        GLESRenderer();

        virtual Material *material() const;
        virtual void setMaterial(Material *material);

        virtual Mesh *mesh() const;
        virtual void setMesh(Mesh *mesh);

        virtual void applySettings();

        virtual void draw() = 0;
        virtual void clear(Color color);

    private:
        Material *mMaterial;
        Mesh *mMesh;
};

class GLESRenderModule : public RenderModule
{
    public:
        GLESRenderModule();

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

    private:
        EGLNativeWindowType mNativeWindow;
        EGLNativeDisplayType mNativeDisplay;
        EGLDisplay mEGLDisplay;
        EGLContext mEGLContext;
        EGLSurface mEGLSurface;
};

} // namespace cepp
