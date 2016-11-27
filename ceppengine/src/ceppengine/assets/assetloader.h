#pragma once

#include <string>
#include "importers/assetimporter.h"
#include "../util/ref.h"
#include "asset.h"

namespace cepp {

class AssetLoader
{
    public:
        struct LoadedAsset
        {
                LoadedAsset(Asset *lAsset, const std::string &lPath) : asset(lAsset), path(lPath) {}

                Ref<Asset> asset;
                std::string path;
        };

        AssetLoader();

        /**
         * Get asset path relative to executable path
         */
        std::string loadPath() const;
        /**
         * Set asset path relative to executable path
         */
        void setLoadPath(const std::string &path);

        /**
         * Load engine default asset importers
         */
        void loadDefaultImporters();

        Asset *loadAsset(const std::string &path, const std::string &type);

        /**
         * Remove assets from asset list, which unloads them if no other references are attached to them.
         */
        void unloadAssets();

    private:
        std::string filePathToAssetPath(const std::string &filePath) const;
        std::string assetPathToFilePath(const std::string &assetPath) const;

        std::string mLoadPath;

        std::vector<Ref<AssetImporter>> mImporters;

        std::vector<LoadedAsset> mLoadedAssets;
};

} // namespace cepp
