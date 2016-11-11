#pragma once

#include "../rendermodule.h"
#include "../../util/ref.h"
#include "EGL/egl.h"
#include "EGL/eglplatform.h"

namespace cepp {

class GLESRenderModule : public RenderModule
{
    public:
        GLESRenderModule();

        void setNativeData(EGLNativeWindowType window, EGLNativeDisplayType display);

        virtual int createShader(Shader *shader);
        virtual void updateShader(int handle, Shader *shader);
        virtual void deleteShader(int handle);

        virtual int createModel(Mesh *mesh);
        virtual void updateModel(int handle, Mesh *mesh);
        virtual void deleteModel(int handle);

        virtual int createTexture(Texture *texture);
        virtual void updateTexture(int handle, Texture *texture);
        virtual void deleteTexture(int handle);

        virtual float *getGlobalShaderParam(std::string name) const;
        virtual void setGlobalShaderParam(std::string name, float value[]);
        virtual void deleteGlobalShaderParam(std::string name);

        virtual void initialize();

    private:
        EGLNativeWindowType mNativeWindow;
        EGLNativeDisplayType mNativeDisplay;
        EGLDisplay mEGLDisplay;
        EGLContext mEGLContext;
        EGLSurface mEGLSurface;
};

} // namespace cepp
