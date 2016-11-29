#include "sprite.h"

namespace cepp {

Sprite::Sprite() : mPivot(Vector3(0.5f, 0.5f)), mTextureCoordinates(Vector3::zero), mSize(Vector3::zero), mPixelsPerUnit(100.f)
{
}

std::string Sprite::typeName() const
{
    return "Sprite";
}

Texture *Sprite::texture() const
{
    return mTexture;
}

void Sprite::setTexture(Texture *texture)
{
    mTexture = texture;
}

Vector3 Sprite::pivot() const
{
    return mPivot;
}

void Sprite::setPivot(const Vector3 &pivot)
{
    mPivot = pivot;
}

Vector3 Sprite::textureCoordinates() const
{
    return mTextureCoordinates;
}

void Sprite::setTextureCoordinates(const Vector3 &texCoords)
{
    mTextureCoordinates = texCoords;
}

Vector3 Sprite::size() const
{
    return mSize;
}

void Sprite::setSize(const Vector3 &size)
{
    mSize = size;
}

float Sprite::pixelsPerUnit() const
{
    return mPixelsPerUnit;
}

void Sprite::setPixelsPerUnit(float ppu)
{
    mPixelsPerUnit = ppu;
}

} // namespace cepp
