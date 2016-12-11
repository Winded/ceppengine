#pragma once

#include "asset.h"
#include "../math/vector3.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../util/ref.h"

namespace cepp {

/**
 * Fonts can be used to render text
 */
class Font : public Asset
{
    public:
        Font(unsigned char *data, int dataSize);
        ~Font();

        virtual std::string typeName() const;

        void load();

        FT_GlyphSlot glyph() const;
        FT_Error loadChar(char c);

    private:
        unsigned char *mData;
        int mDataSize;

        FT_Face mFontFace;
};

} // namespace cepp
