#pragma once

#include "../util/ref.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"

namespace cepp {

/**
 * This class provides default assets. These are used, for example, when no custom shaders are defined to a material,
 * or no texture is provided in a material.
 */
class DefaultAssets
{
    public:
        DefaultAssets();

        Shader *basicShader() const;
        Shader *fontShader() const;
        Texture *whiteTexture() const;
        Mesh *quadMesh() const;

    private:
        Ref<Shader> mBasicShader;
        Ref<Shader> mFontShader;
        Ref<Texture> mWhiteTexture;
        Ref<Mesh> mQuadMesh;
};

} // namespace cepp
