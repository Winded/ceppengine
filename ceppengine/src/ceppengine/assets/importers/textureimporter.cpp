#include "textureimporter.h"
#include <fstream>
#include <iostream>
#include "../texture.h"
#include "../../util/thirdparty/lodepng.h"

namespace cepp {

TextureImporter::TextureImporter()
{

}

bool TextureImporter::canLoadExtension(const std::string &extension) const
{
    return extension == ".png";
}

std::vector<Asset *> TextureImporter::import(std::istream &stream) const
{
    std::vector<Asset*> assets;

    if(stream.eof() || stream.fail())
        return assets;

    std::vector<unsigned char> rawData;

    stream.seekg(0, std::ios_base::end);
    std::streampos fileSize = stream.tellg();
    rawData.resize(fileSize);

    stream.seekg(0, std::ios_base::beg);
    stream.read((char*)(&rawData[0]), fileSize);

    std::vector<unsigned char> sData;
    unsigned int width, height;
    lodepng::decode(sData, width, height, rawData);

    char *data = new char[sData.size()];
    for(int i = 0; i < sData.size(); i++)
        data[i] = sData[i];

    Texture *tex = new Texture(width, height, data);
    assets.push_back(tex);

    return assets;
}

} // namespace cepp
