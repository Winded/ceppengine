#pragma once

#include "asset.h"
#include "texture.h"
#include "../util/ref.h"

namespace cepp {

class Sprite : public Asset
{
    public:
        Sprite();

        Texture *texture() const;
        void setTexture(Texture *texture);

    private:
        Ref<Texture> mTexture;
};

} // namespace cepp
