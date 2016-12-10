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
    mElementBufferLength = indexLength;
    mElementBuffer = new int[mElementBufferLength];
    for(int i = 0; i < mElementBufferLength; i++)
        mElementBuffer[i] = indices[i];

    mVertexBufferLength = verticesLength / 3 * 5;
    mVertexBuffer = new float[mVertexBufferLength];

    int idx = 0;
    int vIdx = 0;
    int uIdx = 0;
    while(true) {
        if(idx > mVertexBufferLength - 5 || vIdx > verticesLength - 3)
            break;

        mVertexBuffer[idx] = vertices[vIdx];
        mVertexBuffer[idx + 1] = vertices[vIdx + 1];
        mVertexBuffer[idx + 2] = vertices[vIdx + 2];
        if(uvCoords && uIdx <= uvCoordsLength - 2) {
            mVertexBuffer[idx + 3] = uvCoords[uIdx];
            mVertexBuffer[idx + 4] = uvCoords[uIdx + 1];
        }
        else {
            mVertexBuffer[idx + 3] = 0;
            mVertexBuffer[idx + 4] = 0;
        }

        idx += 5;
        vIdx += 3;
        uIdx += 2;
    }
}

Mesh::Mesh(const Mesh &otherMesh)
{
    mModuleHandle = -1;

    mVertexBufferLength = otherMesh.mVertexBufferLength;
    mElementBufferLength = otherMesh.mElementBufferLength;

    mVertexBuffer = new float[mVertexBufferLength];
    for(int i = 0; i < mVertexBufferLength; i++)
        mVertexBuffer[i] = otherMesh.mVertexBuffer[i];
    mElementBuffer = new int[mElementBufferLength];
    for(int i = 0; i < mElementBufferLength; i++)
        mElementBuffer[i] = otherMesh.mElementBuffer[i];
}

Mesh::~Mesh()
{
    if(mModuleHandle != -1) {
        Engine::instance()->renderModule()->deleteModel(mModuleHandle);
        mModuleHandle = -1;
    }
    if(mElementBuffer)
        delete mElementBuffer;
    if(mVertexBuffer)
        delete mVertexBuffer;
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

void Mesh::refresh()
{
    if(mModuleHandle != -1) {
        Engine::instance()->renderModule()->updateModel(mModuleHandle, this);
    }
}

float *Mesh::vertexBuffer() const
{
    return mVertexBuffer;
}

int Mesh::vertexBufferLength() const
{
    return mVertexBufferLength;
}

int *Mesh::elementBuffer() const
{
    return mElementBuffer;
}

int Mesh::elementBufferLength() const
{
    return mElementBufferLength;
}

Vector3 Mesh::getVertex(int idx) const
{
    if(idx >= mElementBufferLength)
        return Vector3::zero;
    Vector3 v;
    v.x = mVertexBuffer[idx * 5 + 0];
    v.y = mVertexBuffer[idx * 5 + 1];
    v.z = mVertexBuffer[idx * 5 + 2];
    return v;
}

Vector3 Mesh::getUV(int idx) const
{
    if(idx >= mElementBufferLength)
        return Vector3::zero;
    Vector3 v;
    v.x = mVertexBuffer[idx * 5 + 3];
    v.y = mVertexBuffer[idx * 5 + 4];
    return v;
}

} // namespace cepp
