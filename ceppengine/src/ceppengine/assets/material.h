#pragma once

#include "asset.h"
#include "shader.h"
#include "texture.h"
#include "../util/ref.h"

namespace cepp {

/**
 * Materials tell how a mesh should be rendered. It can provide a texture, shader and shader parameters to be passed to the render API.
 */
class Material : public Asset
{
public:
    struct ShaderParameter {
        std::string name;
        float value[];
    };

    Material();

    Shader *shader() const;
    void setShader(Shader *shader);

    Texture *texture() const;
    void setTexture(Texture *texture);

    float *getShaderParam(std::string name) const;
    void setShaderParam(std::string name, float value[]);
    void deleteShaderParam(std::string name);

private:
    Ref<Shader> mShader;
    Ref<Texture> mTexture;

    std::vector<ShaderParameter> mShaderParameters;
};

} // namespace cepp
