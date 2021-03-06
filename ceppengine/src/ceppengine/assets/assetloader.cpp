#include "assetloader.h"
#include <algorithm>
#include <fstream>
#include "../engine.h"
#include "importers/textureimporter.h"
#include "importers/jsonimporter.h"
#include "importers/shaderimporter.h"
#include "importers/meshimporter.h"
#include "importers/audioimporter.h"
#include "importers/fontimporter.h"

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
    mImporters.push_back(new JsonImporter());
    mImporters.push_back(new ShaderImporter());
    mImporters.push_back(new MeshImporter());
    mImporters.push_back(new AudioImporter());
    mImporters.push_back(new FontImporter());
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
    std::istream *stream = Engine::instance()->fileModule()->getAssetReadStream(path);
    std::vector<Asset*> assets = importer->import(*stream);
    Engine::instance()->fileModule()->closeStream(stream);

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
