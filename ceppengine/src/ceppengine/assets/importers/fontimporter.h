#pragma once

#include "assetimporter.h"

namespace cepp {

class FontImporter : public AssetImporter
{
    public:
        FontImporter();

        virtual bool canLoadExtension(const std::string &extension) const;

        virtual std::vector<Asset*> import(std::istream &stream) const;
};

} // namespace cepp
