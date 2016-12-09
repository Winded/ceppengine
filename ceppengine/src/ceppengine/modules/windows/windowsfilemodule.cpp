#include "windowsfilemodule.h"
#include <Windows.h>
#include <fstream>
#include <string>
#include <codecvt>

namespace cepp {

WindowsFileModule::WindowsFileModule()
{
    wchar_t filePath[1024];
    GetModuleFileName(NULL, filePath, 1024);
    mAssetFolder = getPath(toString(std::wstring(filePath, 1024))) + "/../assets";
}

std::string WindowsFileModule::assetFolder() const
{
    return mAssetFolder;
}

void WindowsFileModule::setAssetFolder(const std::string &folder, bool relative)
{
    if(relative) {
        wchar_t filePath[1024];
        GetModuleFileName(NULL, filePath, 1024);
        mAssetFolder = getPath(toString(std::wstring(filePath, 1024))) + folder;
    }
    else {
        mAssetFolder = folder;
    }
}

std::istream *WindowsFileModule::getAssetReadStream(const std::string &path)
{
    std::string filePath = mAssetFolder + path;
    std::ifstream *stream = new std::ifstream();
    stream->open(filePath, std::ios::binary);
    return stream;
}

std::ostream *WindowsFileModule::getAssetWriteStream(const std::string &path)
{
    std::string filePath = mAssetFolder + path;
    std::ofstream *stream = new std::ofstream();
    stream->open(filePath, std::ios::binary);
    return stream;
}

void WindowsFileModule::closeStream(std::istream *stream)
{
    ((std::ifstream*)stream)->close();
    delete stream;
}

void WindowsFileModule::closeStream(std::ostream *stream)
{
    ((std::ofstream*)stream)->close();
    delete stream;
}

bool WindowsFileModule::assetExists(const std::string &path) const
{
    std::string filePath = mAssetFolder + path;
    DWORD dwAttrib = GetFileAttributes(toWString(filePath).c_str());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
           !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

std::string WindowsFileModule::getPath(const std::string &file) const
{
    size_t found = file.find_last_of("/\\");
    return file.substr(0, found);
}

std::string WindowsFileModule::toString(const std::wstring &str) const
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string narrow = converter.to_bytes(str);
    return narrow;
}

std::wstring WindowsFileModule::toWString(const std::string &str) const
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(str);
    return wide;
}

}
