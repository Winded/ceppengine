#include "material.h"

namespace cepp {

Material::Material()
{

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

float *Material::getShaderParam(std::string name) const
{
    // TODO
    return 0;
}

void Material::setShaderParam(std::string name, float value[])
{
    // TODO
}

void Material::deleteShaderParam(std::string name)
{
    // TODO
}

} // namespace cepp
