#include "shaderimporter.h"
#include <istream>
#include "../shader.h"

namespace cepp {

ShaderImporter::ShaderImporter()
{

}

bool ShaderImporter::canLoadExtension(const std::string &extension) const
{
    return extension == ".shader";
}

std::vector<Asset *> ShaderImporter::import(std::istream &stream) const
{
    std::vector<Asset*> assets;

    if(stream.eof() || stream.fail())
        return assets;

    std::string txt;
    stream.seekg(0, std::ios_base::end);
    std::streampos fileSize = stream.tellg();
    txt.resize(fileSize);

    stream.seekg(0, std::ios_base::beg);
    stream.read((char*)txt.c_str(), fileSize);

    std::string splitStr = "/*#SPLIT#*/";
    std::size_t found = txt.find(splitStr);
    if(found == std::string::npos)
        return assets;

    std::string vertexShader = txt.substr(0, found);
    std::string fragmentShader = txt.substr(found + splitStr.size());

    Shader *shader = new Shader(vertexShader, fragmentShader);
    assets.push_back(shader);

    return assets;
}

} // namespace cepp
