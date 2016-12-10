#pragma once

#include "module.h"
#include "../util/color.h"
#include "../math/vector3.h"
#include "../assets/mesh.h"
#include "../assets/material.h"

namespace cepp {

/**
 * Higher-level, cross-platform interface for low-level rendering APIs, such as OpenGL.
 */
class IRenderer
{
    public:
        virtual Material *material() const = 0;
        virtual void setMaterial(Material *material) = 0;

        virtual Mesh *mesh() const = 0;
        virtual void setMesh(Mesh *mesh) = 0;

        virtual void applySettings() = 0;

        virtual void draw() = 0;
        virtual void clear(Color color) = 0;
};

/**
 * Render module handles graphics rendering.
 */
class RenderModule : public Module
{
    public:
        typedef void (*Callback)(Object*, IRenderer*);

        RenderModule();

        virtual std::string name() const;

        virtual bool vsync() const = 0;
        virtual void setVSync(bool vsync) = 0;

        virtual void addHandler(Object *object, Callback function) = 0;
        virtual void removeHandler(Object *object) = 0;

        /**
         * Load a shader into the graphics API
         */
        virtual int createShader(Shader *shader) = 0;
        /**
         * Update a shader
         */
        virtual void updateShader(int handle, Shader *shader) = 0;
        /**
         * Delete a shader
         */
        virtual void deleteShader(int handle) = 0;

        virtual int createModel(Mesh *mesh) = 0;
        virtual void updateModel(int handle, Mesh *mesh) = 0;
        virtual void deleteModel(int handle) = 0;

        virtual int createTexture(Texture *texture) = 0;
        virtual void updateTexture(int handle, Texture *texture) = 0;
        virtual void deleteTexture(int handle) = 0;

        virtual float *getGlobalShaderParam(const std::string &name, int *size) const = 0;
        virtual void setGlobalShaderParam(const std::string &name, float *value, int size) = 0;
        virtual void deleteGlobalShaderParam(const std::string &name) = 0;
};

} // namespace cepp
