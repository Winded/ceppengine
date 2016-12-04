#pragma once

#include "../component.h"
#include "../../assets/mesh.h"
#include "../../assets/material.h"
#include "../../modules/rendermodule.h"

namespace cepp {

/**
 * Mesh renderer renders a mesh with a given material, relative to the position of the game object.
 */
class MeshRenderer : public Component
{
    public:
        MeshRenderer();
        ~MeshRenderer();

        virtual std::string typeName() const;

        Mesh *mesh() const;
        void setMesh(Mesh *mesh);

        Material *material() const;
        void setMaterial(Material *material);

        void render(IRenderer *renderer);

    protected:
        virtual void start();

    private:
        Ref<Mesh> mMesh;
        Ref<Material> mMaterial;
};

} // namespace cepp
