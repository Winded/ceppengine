#pragma once

#include "assetimporter.h"

namespace Json {
class Value;
}

namespace cepp {

/**
 * JsonImporter can import json data assets, such as sprites and materials
 */
class JsonImporter : public AssetImporter
{
    public:
        JsonImporter();

        virtual bool canLoadExtension(const std::string &extension) const;

        virtual std::vector<Asset*> import(std::istream &stream) const;

    private:
        Asset *createAsset(const Json::Value &jObj) const;
};

} // namespace cepp
