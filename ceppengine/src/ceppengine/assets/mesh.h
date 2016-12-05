#pragma once

#include "asset.h"
#include "../math/vector3.h"

namespace cepp {

/**
 * Meshes contain vertices, vertex indices and UV coordinates, which can be rendered with a Material.
 */
class Mesh : public Asset
{
    public:
        Mesh(float *vertices, int verticesLength, int *elementBuffer, int indexLength);
        Mesh(float *vertices, int verticesLength, float *uvCoords, int uvCoordsLength, int *elementBuffer, int indexLength);
        Mesh(const Mesh &otherMesh);
        ~Mesh();

        virtual std::string typeName() const;

        /**
         * Load mesh into the graphics module, if it is not loaded already
         */
        int load();

        float *vertexBuffer() const;
        int vertexBufferLength() const;

        int *elementBuffer() const;
        int elementBufferLength() const;

        Vector3 getVertex(int idx) const;
        Vector3 getUV(int idx) const;

    private:
        int mModuleHandle;

        float *mVertexBuffer;
        int *mElementBuffer;
        int mElementBufferLength, mVertexBufferLength;
};

} // namespace cepp
