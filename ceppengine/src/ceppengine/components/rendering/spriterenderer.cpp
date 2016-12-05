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
    if(!gameObject()->isActiveInHierarchy()) return;

    renderer->setMesh(mMesh);
    renderer->setMaterial(mMaterial);

    float *lToWMat = gameObject()->localToWorldMatrix().toColumnMajorArray();
    float *color = mColor.toNormalizedArray();
    Engine::instance()->renderModule()->setGlobalShaderParam("LocalToWorldMatrix", lToWMat, 4 * 4);
    Engine::instance()->renderModule()->setGlobalShaderParam("BaseColor", color, 4);

    renderer->applySettings();
    renderer->draw();

    delete lToWMat;
    delete color;
}

void _renderSprite(Object *obj, IRenderer *renderer)
{
    SpriteRenderer *spriteR = (SpriteRenderer*)obj;
    spriteR->render(renderer);
}

void SpriteRenderer::start()
{
    Engine::instance()->renderModule()->addHandler(this, _renderSprite);

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

    float *vBuf = mMesh->vertexBuffer();

    Vector3 spriteSize = Vector3(mSprite->size().x, mSprite->size().y, 0) / mSprite->pixelsPerUnit();
    Vector3 tl = spriteSize * Vector3(-mSprite->pivot().x, mSprite->pivot().y, 0);
    Vector3 tr = spriteSize * Vector3(1 - mSprite->pivot().x, mSprite->pivot().y, 0);
    Vector3 br = spriteSize * Vector3(1 - mSprite->pivot().x, mSprite->pivot().y - 1, 0);
    Vector3 bl = spriteSize * Vector3(-mSprite->pivot().x, mSprite->pivot().y - 1, 0);

    vBuf[0] = tl.x; vBuf[1] = tl.y; vBuf[2] = tl.z;
    vBuf[5] = tr.x; vBuf[6] = tr.y; vBuf[7] = tr.z;
    vBuf[10] = br.x; vBuf[11] = br.y; vBuf[12] = br.z;
    vBuf[15] = bl.x; vBuf[16] = bl.y; vBuf[17] = bl.z;
}

void SpriteRenderer::calculateTexCoords()
{
    if(!mSprite || !mSprite->texture()) return;

    float *vBuf = mMesh->vertexBuffer();

    Vector3 textureSize = Vector3(mSprite->texture()->width(), mSprite->texture()->height(), 0);
    Vector3 tl = Vector3(mSprite->textureCoordinates().x, mSprite->textureCoordinates().y, 0) / textureSize;
    Vector3 tr = Vector3(mSprite->textureCoordinates().x + mSprite->size().x, mSprite->textureCoordinates().y, 0) / textureSize;
    Vector3 br = Vector3(mSprite->textureCoordinates().x + mSprite->size().x, mSprite->textureCoordinates().y + mSprite->size().y, 0) / textureSize;
    Vector3 bl = Vector3(mSprite->textureCoordinates().x, mSprite->textureCoordinates().y + mSprite->size().y, 0) / textureSize;

    vBuf[3] = tl.x; vBuf[4] = tl.y;
    vBuf[8] = tr.x; vBuf[9] = tr.y;
    vBuf[13] = br.x; vBuf[14] = br.y;
    vBuf[18] = bl.x; vBuf[19] = bl.y;
}

} // namespace cepp
