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
    aiScene *scene = importer.ReadFileFromMemory(data.c_str(), data.size(), aiProcess_Triangulate | aiProcess_TransformUVCoords);

    if(!scene)
        return assets;

    for(int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *aMesh = scene->mMeshes[i];
        float verts[aMesh->mNumVertices * 3];
        int ii = 0;
        while(ii < aMesh->mNumVertices * 3) {
            aiVector3D vec = aMesh->mVertices[ii];
            verts[ii] = vec.x;
            verts[ii + 1] = vec.y;
            verts[ii + 2] = vec.z;
            ii += 3;
        }
        unsigned int indices[aMesh->mNumFaces];
        ii = 0;
        while(ii < aMesh->mNumFaces) {
            aiFace face = aMesh->mFaces[ii];
            assert(face.mNumIndices == 3);
            indices[ii] = face.mIndices[0];
            indices[ii + 1] = face.mIndices[1];
            indices[ii + 2] = face.mIndices[2];
            ii++;
        }

        Mesh *mesh = 0;
        if(aMesh->HasTextureCoords(0)) {
            float texCoords[aMesh->mNumVertices * 2];
            ii = 0;
            while(ii < aMesh->mNumVertices * 2) {
                aiVector3D texC = aMesh->mTextureCoords[ii];
                texCoords[ii] = texC.x;
                texCoords[ii + 1] = texC.y;
                ii += 2;
            }
            mesh = new Mesh(verts, aMesh->mNumVertices * 3, texCoords, aMesh->mNumVertices * 2, indices, aMesh->mNumFaces);
        }
        else {
            mesh = new Mesh(verts, aMesh->mNumVertices * 3, indices, aMesh->mNumFaces);
        }

        assets.push_back(mesh);
    }

    return assets;
}

} // namespace cepp
