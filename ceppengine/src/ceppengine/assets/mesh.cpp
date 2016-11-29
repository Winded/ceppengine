#include "mesh.h"
#include "../engine.h"

namespace cepp {

Mesh::Mesh(float *vertices, int verticesLength, int *indices, int indexLength) :
    Mesh(vertices, verticesLength, 0, 0, indices, indexLength)
{
}

Mesh::Mesh(float *vertices, int verticesLength,
           float *uvCoords, int uvCoordsLength,
           int *indices, int indexLength) :
    mModuleHandle(-1)
{
    mVertices = vertices;
    mVertexLength = verticesLength;
    mUVCoordinates = uvCoords;
    mUVCoordinatesLength = uvCoordsLength;
    mIndices = indices;
    mIndexLength = indexLength;
}

Mesh::Mesh(const Mesh &otherMesh)
{
    mModuleHandle = -1;

    mVertexLength = otherMesh.mVertexLength;
    mUVCoordinatesLength = otherMesh.mUVCoordinatesLength;
    mIndexLength = otherMesh.mIndexLength;

    mVertices = new float[mVertexLength];
    for(int i = 0; i < mVertexLength; i++)
        mVertices[i] = otherMesh.mVertices[i];
    mUVCoordinates = new float[mUVCoordinatesLength];
    for(int i = 0; i < mUVCoordinatesLength; i++)
        mUVCoordinates[i] = otherMesh.mUVCoordinates[i];
    mIndices = new int[mIndexLength];
    for(int i = 0; i < mIndexLength; i++)
        mIndices[i] = otherMesh.mIndices[i];
}

Mesh::~Mesh()
{
    if(mModuleHandle != -1) {
        Engine::instance()->renderModule()->deleteModel(mModuleHandle);
        mModuleHandle = -1;
    }
    if(mVertices)
        delete mVertices;
    if(mUVCoordinates)
        delete mUVCoordinates;
    if(mIndices)
        delete mIndices;
}

std::string Mesh::typeName() const
{
    return "Mesh";
}

int Mesh::load()
{
    if(mModuleHandle == -1)
        mModuleHandle = Engine::instance()->renderModule()->createModel(this);
    return mModuleHandle;
}

float *Mesh::vertices() const
{
    return mVertices;
}

int Mesh::verticesLength() const
{
    return mVertexLength;
}

float *Mesh::uvCoordinates() const
{
    return mUVCoordinates;
}

int Mesh::uvCoordinatesLength() const
{
    return mUVCoordinatesLength;
}

int *Mesh::indices() const
{
    return mIndices;
}

int Mesh::indicesLength() const
{
    return mIndexLength;
}

} // namespace cepp
