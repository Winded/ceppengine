#include "sprite.h"

namespace cepp {

Sprite::Sprite()
{

}

Texture *Sprite::texture() const
{
    return mTexture;
}

void Sprite::setTexture(Texture *texture)
{
    mTexture = texture;
}

} // namespace cepp
