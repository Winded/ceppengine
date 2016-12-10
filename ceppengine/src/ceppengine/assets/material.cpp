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
    auto it = std::find_if(mShaderParams.begin(), mShaderParams.end(), [name](const ShaderParameter &param) {
       return param.name == name;
    });

    if(it != mShaderParams.end()) {
        // Parameter exists, but is different size; do realloc
        if(size != (*it).size)
            realloc((*it).data, size * sizeof(float));
        memcpy((*it).data, value, size * sizeof(float));
        (*it).size = size;
    }
    else {
        // Create new parameter
        float *data = new float[size];
        memcpy(data, value, size * sizeof(float));
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
