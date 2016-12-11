#include "font.h"
#include "../engine.h"

namespace cepp {

Font::Font(unsigned char *data, int dataSize) : mData(data), mDataSize(dataSize), mFontFace(0)
{
}

Font::~Font()
{
    delete mData;
}

std::string Font::typeName() const
{
    return "Font";
}

void Font::load()
{
    if (!mFontFace) {
        FT_New_Memory_Face(Engine::instance()->renderModule()->fontLibrary(), mData, mDataSize, 0, &mFontFace);
        FT_Set_Pixel_Sizes(mFontFace, 0, 48);
    }
}

FT_GlyphSlot Font::glyph() const
{
    return mFontFace->glyph;
}

FT_Error Font::loadChar(char c)
{
    return FT_Load_Char(mFontFace, c, FT_LOAD_RENDER);
}

} // namespace cepp
