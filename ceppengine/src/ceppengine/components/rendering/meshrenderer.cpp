#include "meshrenderer.h"
#include "../../engine.h"

namespace cepp {

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::~MeshRenderer()
{
    Engine::instance()->renderModule()->removeHandler(this);
}

std::string MeshRenderer::typeName() const
{
    return "MeshRenderer";
}

Mesh *MeshRenderer::mesh() const
{
    return mMesh;
}

void MeshRenderer::setMesh(Mesh *mesh)
{
    mMesh = mesh;
}

Material *MeshRenderer::material() const
{
    return mMaterial;
}

void MeshRenderer::setMaterial(Material *material)
{
    mMaterial = material;
}

void _renderMesh(Object *obj, IRenderer *renderer)
{
    MeshRenderer *r = (MeshRenderer*)obj;
    r->render(renderer);
}

void MeshRenderer::render(IRenderer *renderer)
{
    if(!gameObject()->isActiveInHierarchy()) return;

    renderer->setMesh(mMesh);
    renderer->setMaterial(mMaterial);

    float *lToWMat = gameObject()->localToWorldMatrix().toColumnMajorArray();
    Engine::instance()->renderModule()->setGlobalShaderParam("LocalToWorldMatrix", lToWMat, 4 * 4);

    renderer->applySettings();
    renderer->draw();

    delete lToWMat;
}

void MeshRenderer::start()
{
    Engine::instance()->renderModule()->addHandler(this, _renderMesh);
}

} // namespace cepp
