#pragma once

#include "assetimporter.h"

namespace cepp {

/**
 * AudioImporter
 */
class AudioImporter : public AssetImporter
{
    public:
        AudioImporter();

        virtual bool canLoadExtension(const std::string &extension) const;

        virtual std::vector<Asset*> import(std::istream &stream) const;
};

} // namespace cepp
