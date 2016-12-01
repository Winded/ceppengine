#pragma once

#include "assetimporter.h"

namespace cepp {

class ShaderImporter : public AssetImporter
{
    public:
        ShaderImporter();

        virtual bool canLoadExtension(const std::string &extension) const;

        virtual std::vector<Asset*> import(std::istream &stream) const;
};

} // namespace cepp
