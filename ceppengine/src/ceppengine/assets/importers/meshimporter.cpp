#include "meshimporter.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "../mesh.h"

namespace cepp {

MeshImporter::MeshImporter()
{

}

bool MeshImporter::canLoadExtension(const std::string &extension) const
{
    return extension == ".obj";
}

std::vector<Asset *> MeshImporter::import(std::istream &stream) const
{
    std::vector<Asset*> assets;

    if(stream.eof() || stream.fail())
        return assets;

    std::string data;
    stream.seekg(0, std::ios_base::end);
    std::streampos fileSize = stream.tellg();
    data.resize(fileSize);

    stream.seekg(0, std::ios_base::beg);
    stream.read((char*)data.c_str(), fileSize);

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFileFromMemory(data.c_str(), data.size(), aiProcess_Triangulate | aiProcess_TransformUVCoords);

    if(!scene)
        return assets;

    for(int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *aMesh = scene->mMeshes[i];
        float *verts = new float[aMesh->mNumVertices * 3];
        for(int ii = 0; ii < aMesh->mNumVertices; ii++) {
            aiVector3D vec = aMesh->mVertices[ii];
            verts[ii * 3 + 0] = vec.x;
            verts[ii * 3 + 1] = vec.y;
            verts[ii * 3 + 2] = vec.z;
        }
        int *indices = new int[aMesh->mNumFaces * 3];
        for(int ii = 0; ii < aMesh->mNumFaces; ii++) {
            aiFace face = aMesh->mFaces[ii];
            assert(face.mNumIndices == 3);
            indices[ii * 3 + 0] = face.mIndices[0];
            indices[ii * 3 + 1] = face.mIndices[1];
            indices[ii * 3 + 2] = face.mIndices[2];
        }

        Mesh *mesh = 0;
        if(aMesh->HasTextureCoords(0)) {
            float *texCoords = new float[aMesh->mNumVertices / 3 * 2];
            for(int ii = 0; ii < aMesh->mNumVertices / 3 * 2; ii++) {
                aiVector3D *texC = aMesh->mTextureCoords[ii];
                texCoords[ii * 2 + 0] = texC->x;
                texCoords[ii * 2 + 1] = texC->y;
            }
            mesh = new Mesh(verts, aMesh->mNumVertices * 3, texCoords, aMesh->mNumVertices * 2, indices, aMesh->mNumFaces * 3);
        }
        else {
            mesh = new Mesh(verts, aMesh->mNumVertices * 3, indices, aMesh->mNumFaces * 3);
        }

        assets.push_back(mesh);
    }

    return assets;
}

} // namespace cepp
