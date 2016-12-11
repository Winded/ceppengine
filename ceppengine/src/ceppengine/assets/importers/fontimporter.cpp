#include "fontimporter.h"
#include "../font.h"
#include <istream>

namespace cepp {

FontImporter::FontImporter()
{

}

bool FontImporter::canLoadExtension(const std::string &extension) const
{
    return extension == ".ttf";
}

std::vector<Asset *> FontImporter::import(std::istream &stream) const
{
    std::vector<Asset*> assets;

    if(stream.fail() || stream.eof())
        return assets;

    stream.seekg(0, std::ios_base::end);
    std::streampos fileSize = stream.tellg();
    char *data = new char[fileSize];
    stream.seekg(0, std::ios_base::beg);
    stream.read(data, fileSize);

    Font *font = new Font((unsigned char*)data, fileSize);
    assets.push_back(font);
    return assets;
}

} // namespace cepp
