#pragma once

#include "asset.h"

namespace cepp {

/**
 * Textures are used to render pixels onto the surface of a mesh. In terms of assets, it's basically a PNG image file.
 */
class Texture : public Asset
{
public:
    Texture();
};

} // namespace cepp
