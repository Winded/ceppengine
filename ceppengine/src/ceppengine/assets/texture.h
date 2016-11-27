#pragma once

#include "asset.h"

namespace cepp {

/**
 * Textures are used to render pixels onto the surface of a mesh. In terms of assets, it's basically a PNG image file.
 */
class Texture : public Asset
{
    public:
        Texture(int width, int height, void *data);
        ~Texture();

        virtual std::string typeName() const;

        /**
         * Load texture into the graphics module, if it is not loaded already
         */
        int load();

        int width() const;
        int height() const;
        const void *data() const;

    private:
        int mModuleHandle;

        int mWidth, mHeight;
        void *mData;
};

} // namespace cepp
