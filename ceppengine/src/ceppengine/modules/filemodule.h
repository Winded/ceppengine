#pragma once

#include "module.h"

namespace cepp {

/**
 * File modules can be used for platform-neutral filesystem/asset operations
 */
class FileModule : public Module
{
    public:
        FileModule();

        virtual std::string name() const;

        virtual std::istream *getAssetReadStream(const std::string &path) = 0;
        virtual std::ostream *getAssetWriteStream(const std::string &path) = 0;

        virtual void closeStream(std::istream *stream) = 0;
        virtual void closeStream(std::ostream *stream) = 0;

        virtual bool assetExists(const std::string &path) const = 0;
};

}
