#pragma once

#include "asset.h"

namespace cepp {

class Shader : public Asset
{
    public:
        Shader(const std::string &source);
        Shader(const std::string &vertexSource, const std::string &fragmentSource);
        ~Shader();

        virtual std::string typeName() const;

        /**
         * Load the shader into the graphics module, if it is not loaded already
         */
        int load();

        const char *vertexShaderSource() const;
        int vertexShaderSourceLength() const;

        const char *fragmentShaderSource() const;
        int fragmentShaderSourceLength() const;

    private:
        int mModuleHandle;

        std::string mVertexSource;
        std::string mFragmentSource;
};

} // namespace cepp
