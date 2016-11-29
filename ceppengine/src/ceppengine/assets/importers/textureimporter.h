#pragma once

#include "assetimporter.h"

namespace cepp {

/**
 * Asset importer for textures (PNG files)
 */
class TextureImporter : public AssetImporter
{
    public:
        TextureImporter();

        virtual bool canLoadExtension(const std::string &extension) const;

        virtual std::vector<Asset*> import(std::istream &stream) const;
};

} // namespace cepp
