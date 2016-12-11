#include "texture.h"
#include "../engine.h"

namespace cepp {

Texture::Texture(int width, int height, void *data) :
    mModuleHandle(-1), mWidth(width), mHeight(height), mData(data)
{

}

Texture::~Texture()
{
    if(mModuleHandle != -1) {
        Engine::instance()->renderModule()->deleteTexture(mModuleHandle);
        mModuleHandle = -1;
    }
    delete mData;
}

std::string Texture::typeName() const
{
    return "Texture";
}

int Texture::load()
{
    if(mModuleHandle == -1)
        mModuleHandle = Engine::instance()->renderModule()->createTexture(this);
    return mModuleHandle;
}

void Texture::refresh(int width, int height, void *data, bool greyscale)
{
    mWidth = width;
    mHeight = height;
    mData = data;

    if(mModuleHandle != -1)
        Engine::instance()->renderModule()->updateTexture(mModuleHandle, this, greyscale);
}

int Texture::width() const
{
    return mWidth;
}

int Texture::height() const
{
    return mHeight;
}

const void *Texture::data() const
{
    return mData;
}

} // namespace cepp
