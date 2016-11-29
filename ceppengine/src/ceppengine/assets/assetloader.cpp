#include "assetloader.h"
#include <algorithm>
#include <fstream>
#include "importers/textureimporter.h"

namespace cepp {

AssetLoader::AssetLoader()
{
    mLoadPath = "../assets";
}

std::string AssetLoader::loadPath() const
{
    return mLoadPath;
}

void AssetLoader::setLoadPath(const std::string &path)
{
    mLoadPath = path;
}

void AssetLoader::loadDefaultImporters()
{
    mImporters.push_back(new TextureImporter());
    // TODO
}

Asset *AssetLoader::loadAsset(const std::string &path, const std::string &type)
{
    // See if we have already loaded this asset
    auto asIt = std::find_if(mLoadedAssets.begin(), mLoadedAssets.end(), [path, type](const LoadedAsset &asset) {
        return asset.path == path && asset.asset && asset.asset->typeName() == type;
    });
    if(asIt != mLoadedAssets.end())
        return (*asIt).asset;

    // Get the right importer for the asset file
    std::string ext = path.substr(path.find_last_of('.'));
    AssetImporter *importer = 0;
    for(auto it = mImporters.begin(); it != mImporters.end(); ++it) {
        if((*it)->canLoadExtension(ext)) {
            importer = *it;
            break;
        }
    }
    if(!importer)
        return 0;

    // Open input stream
    std::string filePath = assetPathToFilePath(path);
    std::ifstream stream;
    stream.open(filePath, std::ios::binary);
    std::vector<Asset*> assets = importer->import(stream);
    stream.close();

    Asset *rAsset = 0;
    for(auto it = assets.begin(); it != assets.end(); ++it) {
        if((*it)->typeName() == type)
            rAsset = *it;
        mLoadedAssets.push_back(AssetLoader::LoadedAsset(*it, path));
    }
    return rAsset;
}

void AssetLoader::unloadAssets()
{
    mLoadedAssets.clear();
}

std::string AssetLoader::filePathToAssetPath(const std::string &filePath) const
{
    assert(filePath.size() > mLoadPath.size());
    std::string path = "/" + filePath.substr(mLoadPath.size() + 1);
    std::replace(path.begin(), path.end(), '\\', '/');
    return path;
}

std::string AssetLoader::assetPathToFilePath(const std::string &assetPath) const
{
    return mLoadPath + assetPath;
}

} // namespace cepp
