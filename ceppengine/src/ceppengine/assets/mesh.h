#pragma once

#include "asset.h"

namespace cepp {

/**
 * Meshes contain vertices, vertex indices and UV coordinates, which can be rendered with a Material.
 */
class Mesh : public Asset
{
    public:
        Mesh(float *vertices, int verticesLength, int *indices, int indexLength);
        Mesh(float *vertices, int verticesLength, float *uvCoords, int uvCoordsLength, int *indices, int indexLength);
        Mesh(const Mesh &otherMesh);
        ~Mesh();

        /**
         * Load mesh into the graphics module, if it is not loaded already
         */
        int load();

        float *vertices() const;
        int verticesLength() const;

        float *uvCoordinates() const;
        int uvCoordinatesLength() const;

        int *indices() const;
        int indicesLength() const;

    private:
        int mModuleHandle;

        float *mVertices, *mUVCoordinates;
        int *mIndices;
        int mVertexLength, mUVCoordinatesLength, mIndexLength;
};

} // namespace cepp
