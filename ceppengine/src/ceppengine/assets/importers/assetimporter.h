#pragma once

#include "../../object.h"
#include "../asset.h"

namespace cepp {

/**
 * Asset importers can import Asset object or several objects from an asset file.
 * These basically determine how to convert the file data stream into a usable asset object.
 */
class AssetImporter : public Object
{
    public:
        AssetImporter();

        /**
         * Can this asset loader handle the given file extension?
         */
        virtual bool canLoadExtension(const std::string &extension) const = 0;

        /**
         * Import assets from given data stream.
         */
        virtual std::vector<Asset*> import(std::istream &stream) const = 0;
};

} // namespace cepp
