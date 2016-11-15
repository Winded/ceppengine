#include "shader.h"
#include "../engine.h"

namespace cepp {

Shader::Shader(const std::string &source) : mModuleHandle(-1)
{
    // TODO
}

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource)
    : mModuleHandle(-1), mVertexSource(vertexSource), mFragmentSource(fragmentSource)
{
}

Shader::~Shader()
{
    if(mModuleHandle != -1) {
        Engine::instance()->renderModule()->deleteShader(mModuleHandle);
        mModuleHandle = -1;
    }
}

int Shader::load()
{
    if(mModuleHandle == -1)
        mModuleHandle = Engine::instance()->renderModule()->createShader(this);
    return mModuleHandle;
}

const char *Shader::vertexShaderSource() const
{
    return mVertexSource.c_str();
}

int Shader::vertexShaderSourceLength() const
{
    return mVertexSource.size();
}

const char *Shader::fragmentShaderSource() const
{
    return mFragmentSource.c_str();
}

int Shader::fragmentShaderSourceLength() const
{
    return mFragmentSource.size();
}

} // namespace cepp
