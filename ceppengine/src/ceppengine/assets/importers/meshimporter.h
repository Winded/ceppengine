#pragma once

#include "assetimporter.h"

namespace cepp {

/**
 * @brief The MeshImporter class
 */
class MeshImporter : public AssetImporter
{
    public:
        MeshImporter();

        virtual bool canLoadExtension(const std::string &extension) const;

        virtual std::vector<Asset *> import(std::istream &stream) const;
};

} // namespace cepp
