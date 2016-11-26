#include "spriterenderer.h"
#include "../../engine.h"

namespace cepp {

SpriteRenderer::SpriteRenderer() : mColor(Color::white)
{

}

SpriteRenderer::~SpriteRenderer()
{
    Engine::instance()->renderModule()->removeHandler(this);
}

std::string SpriteRenderer::typeName() const
{
    return "SpriteRenderer";
}

Sprite *SpriteRenderer::sprite() const
{
    return mSprite;
}

void SpriteRenderer::setSprite(Sprite *sprite)
{
    mSprite = sprite;
}

Color SpriteRenderer::color() const
{
    return mColor;
}

void SpriteRenderer::setColor(const Color &color)
{
    mColor = color;
}

void SpriteRenderer::render(IRenderer *renderer)
{
    if(!gameObject()->isActive()) return;

    renderer->setMesh(mMesh);
    renderer->setMaterial(mMaterial);

    float *lToWMat = gameObject()->localToWorldMatrix().toArray();
    float *color = new float[4] { (float)mColor.r, (float)mColor.g, (float)mColor.b, (float)mColor.a };
    Engine::instance()->renderModule()->setGlobalShaderParam("LocalToWorldMatrix", lToWMat, 4 * 4);
    Engine::instance()->renderModule()->setGlobalShaderParam("BaseColor", color, 4);

    renderer->applySettings();
    renderer->draw();

    delete lToWMat;
    delete color;
}

void _render(Object *obj, IRenderer *renderer)
{
    SpriteRenderer *spriteR = (SpriteRenderer*)obj;
    spriteR->render(renderer);
}

void SpriteRenderer::start()
{
    Engine::instance()->renderModule()->addHandler(this, _render);

    mMaterial = new Material();
    mMaterial->setShader(Engine::instance()->defaultAssets()->basicShader());
    mMaterial->setTexture(mSprite ? mSprite->texture() : Engine::instance()->defaultAssets()->whiteTexture());

    Mesh *quad = Engine::instance()->defaultAssets()->quadMesh();
    mMesh = new Mesh(*quad);
    calculateVertices();
    calculateTexCoords();
}

void SpriteRenderer::calculateVertices()
{
    if(!mSprite) return;

    float *verts = mMesh->vertices();

    Vector3 spriteSize = Vector3(mSprite->size().x, mSprite->size().y, 0) / mSprite->pixelsPerUnit();
    Vector3 tl = spriteSize * Vector3(-mSprite->pivot().x, mSprite->pivot().y, 0);
    Vector3 tr = spriteSize * Vector3(1 - mSprite->pivot().x, mSprite->pivot().y, 0);
    Vector3 br = spriteSize * Vector3(1 - mSprite->pivot().x, mSprite->pivot().y - 1, 0);
    Vector3 bl = spriteSize * Vector3(-mSprite->pivot().x, mSprite->pivot().y - 1, 0);

    verts[0] = tl.x; verts[1] = tl.y; verts[2] = tl.z;
    verts[3] = tr.x; verts[4] = tr.y; verts[5] = tr.z;
    verts[6] = br.x; verts[7] = br.y; verts[8] = br.z;
    verts[9] = bl.x; verts[9] = bl.y; verts[9] = bl.z;
}

void SpriteRenderer::calculateTexCoords()
{
    if(!mSprite || !mSprite->texture()) return;

    float *texCoords = mMesh->uvCoordinates();

    Vector3 textureSize = Vector3(mSprite->texture()->width(), mSprite->texture()->height(), 0);
    Vector3 tl = Vector3(mSprite->textureCoordinates().x, mSprite->textureCoordinates().y, 0) / textureSize;
    Vector3 tr = Vector3(mSprite->textureCoordinates().x + mSprite->size().x, mSprite->textureCoordinates().y, 0) / textureSize;
    Vector3 br = Vector3(mSprite->textureCoordinates().x + mSprite->size().x, mSprite->textureCoordinates().y + mSprite->size().y, 0) / textureSize;
    Vector3 bl = Vector3(mSprite->textureCoordinates().x, mSprite->textureCoordinates().y + mSprite->size().y, 0) / textureSize;

    texCoords[0] = tl.x; texCoords[1] = tl.y;
    texCoords[2] = tr.x; texCoords[3] = tr.y;
    texCoords[4] = br.x; texCoords[5] = br.y;
    texCoords[6] = bl.x; texCoords[7] = bl.y;
}

} // namespace cepp
