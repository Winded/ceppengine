#include "material.h"
#include <algorithm>

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
    return mShaderParams;
}

float *Material::getShaderParam(std::string name, int *size) const
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

void Material::setShaderParam(std::string name, float *value, int size)
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

void Material::deleteShaderParam(std::string name)
{
    auto it = std::find_if(mShaderParams.begin(), mShaderParams.end(), [name](const ShaderParameter &param) {
       return param.name == name;
    });

    if(it != mShaderParams.end()) {
        delete (*it).data;
        it = mShaderParams.erase(it);
    }
}

} // namespace cepp
