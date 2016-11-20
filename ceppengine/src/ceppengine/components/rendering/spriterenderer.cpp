#include "spriterenderer.h"
#include "../../engine.h"

namespace cepp {

SpriteRenderer::SpriteRenderer()
{

}

SpriteRenderer::~SpriteRenderer()
{
    Engine::instance()->renderModule()->removeHandler(this);
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
    float *color = new float[] { mColor.r, mColor.g, mColor.b, mColor.a };
    Engine::instance()->renderModule()->setGlobalShaderParam("LocalToWorldMatrix", lToWMat, 4 * 4);
    Engine::instance()->renderModule()->setGlobalShaderParam("BaseColor", color, 4);
    delete lToWMat;
    delete color;

    renderer->applySettings();
    renderer->draw();
}

void render(Object *obj, IRenderer *renderer)
{
    SpriteRenderer *spriteR = (SpriteRenderer*)obj;
    spriteR->render(renderer);
}

void SpriteRenderer::start()
{
    Engine::instance()->renderModule()->addHandler(this, render);

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

    verts[0] = tl;
    verts[1] = tr;
    verts[2] = br;
    verts[3] = bl;
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

    texCoords[0] = tl;
    texCoords[1] = tr;
    texCoords[2] = br;
    texCoords[3] = bl;
}

} // namespace cepp
