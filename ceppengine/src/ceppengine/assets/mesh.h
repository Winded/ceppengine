#pragma once

#include "asset.h"

namespace cepp {

/**
 * Meshes contain vertices, vertex indices and UV coordinates, which can be rendered with a Material.
 */
class Mesh : public Asset
{
public:
    Mesh();
};

} // namespace cepp
