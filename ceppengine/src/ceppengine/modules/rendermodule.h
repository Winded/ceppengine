#pragma once

#include "module.h"
#include "../util/color.h"
#include "../assets/mesh.h"
#include "../assets/material.h"

namespace cepp {

/**
 * Higher-level, cross-platform interface for low-level rendering APIs, such as OpenGL.
 */
class IRenderer {
public:
    virtual Material *material() const = 0;
    virtual void setMaterial(Material *material) = 0;

    virtual Mesh *mesh() const = 0;
    virtual void setMesh(Mesh *mesh);

    virtual void applySettings() = 0;

    virtual void draw() = 0;
    virtual void clear(Color color);
};

/**
 * Render module handles graphics rendering.
 */
class RenderModule : public Module
{
public:
    RenderModule();
};

} // namespace cepp
