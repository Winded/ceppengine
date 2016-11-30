#include "material.h"

namespace cepp {

Material::Material()
{

}

std::string Material::typeName() const
{
    return "Material";
}

Shader *Material::shader() const
{
    return mShader;
}

void Material::setShader(Shader *shader)
{
    mShader = shader;
}

Texture *Material::texture() const
{
    return mTexture;
}

void Material::setTexture(Texture *texture)
{
    mTexture = texture;
}

const std::vector<ShaderParameter> &Material::shaderParameters() const
{
    return mShaderParameters;
}

float *Material::getShaderParam(std::string name, int *size) const
{
    // TODO
    return 0;
}

void Material::setShaderParam(std::string name, float *value, int size)
{
    // TODO
}

void Material::deleteShaderParam(std::string name)
{
    // TODO
}

} // namespace cepp
