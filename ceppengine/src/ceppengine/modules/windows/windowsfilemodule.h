#pragma once

#include "../filemodule.h"

namespace cepp {

/**
 * File module for windows
 */
class WindowsFileModule : public FileModule
{
    public:
        WindowsFileModule();

        std::string assetFolder() const;
        void setAssetFolder(const std::string &folder, bool relative);

        virtual std::istream *getAssetReadStream(const std::string &path);
        virtual std::ostream *getAssetWriteStream(const std::string &path);

        virtual void closeStream(std::istream *stream);
        virtual void closeStream(std::ostream *stream);

        virtual bool assetExists(const std::string &path) const;

    private:
        std::string getPath(const std::string &file) const;
        std::string toString(const std::wstring &str) const;
        std::wstring toWString(const std::string &str) const;

        std::string mAssetFolder;
};

}
