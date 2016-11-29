#pragma once

#include "asset.h"
#include "texture.h"
#include "../util/ref.h"
#include "../util/color.h"
#include "../math/vector3.h"

namespace cepp {

class Sprite : public Asset
{
    public:
        Sprite();

        virtual std::string typeName() const;

        Texture *texture() const;
        void setTexture(Texture *texture);

        Vector3 pivot() const;
        void setPivot(const Vector3 &pivot);

        Vector3 textureCoordinates() const;
        void setTextureCoordinates(const Vector3 &texCoords);

        Vector3 size() const;
        void setSize(const Vector3 &size);

        float pixelsPerUnit() const;
        void setPixelsPerUnit(float ppu);

    private:
        Ref<Texture> mTexture;

        Vector3 mPivot;

        Vector3 mTextureCoordinates, mSize;

        float mPixelsPerUnit;
};

} // namespace cepp
