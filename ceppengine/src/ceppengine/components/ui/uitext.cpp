#include "uitext.h"
#include "../../engine.h"

namespace cepp {

UIText::UIText() : mText("Text"), mFontSize(48), mColor(Color::white)
{
}

UIText::~UIText()
{
    Engine::instance()->renderModule()->removeHandler(this);
}

std::string UIText::typeName() const
{
    return "UIText";
}

std::string UIText::text() const
{
    return mText;
}

void UIText::setText(const std::string &text)
{
    mText = text;
}

Font *UIText::font() const
{
    return mFont;
}

void UIText::setFont(Font *font)
{
    mFont = font;
}

float UIText::fontSize() const
{
    return mFontSize;
}

void UIText::setFontSize(float size)
{
    mFontSize = size;
}

Color UIText::color() const
{
    return mColor;
}

void UIText::setColor(const Color &color)
{
    mColor = color;
}

void UIText::render(IRenderer *renderer)
{
    if(!gameObject()->isActiveInHierarchy()) return;
    if(mText.empty() || !mFont) return;

    Vector3 screen = Engine::instance()->runtimeModule()->screenResolution();

    mFont->load();

    renderer->setMesh(mMesh);
    renderer->setMaterial(mMaterial);

    float *color = mColor.toNormalizedArray();
    Engine::instance()->renderModule()->setGlobalShaderParam("BaseColor", color, 4);
    delete color;

    FT_GlyphSlot g = mFont->glyph();

    float x = (gameObject()->position().x / screen.x) * 2.f - 1.f;
    float y = (gameObject()->position().y / screen.y) * 2.f - 1.f;
    float sx = 2.f / screen.x * mFontSize / 48.f;
    float sy = 2.f / screen.y * mFontSize / 48.f;

    const char *text = mText.c_str();
    const char *p;
    for(p = text; *p; p++) {
        FT_Error err = mFont->loadChar(*p);
        if(err)
            continue;

        mTexture->refresh(g->bitmap.width, g->bitmap.rows, g->bitmap.buffer, true);

        float x2 = x + g->bitmap_left * sx;
        float y2 = -y - g->bitmap_top * sy;
        float w = g->bitmap.width * sx;
        float h = g->bitmap.rows * sy;

        float *v = mMesh->vertexBuffer();

        v[0] = x2;      v[1] = -y2;         v[2] = 0;   v[3] = 0; v[4] = 0;
        v[5] = x2 + w;  v[6] = -y2;         v[7] = 0;   v[8] = 1; v[9] = 0;
        v[10] = x2;     v[11] = -y2 - h;    v[12] = 0;  v[13] = 0; v[14] = 1;
        v[15] = x2 + w; v[16] = -y2 - h;    v[17] = 0;  v[18] = 1; v[19] = 1;

        mMesh->refresh();

        renderer->applySettings();
        renderer->draw();

        x += (g->advance.x >> 6) * sx;
        y += (g->advance.y >> 6) * sy;
    }
}

void _render(Object *object, IRenderer *renderer)
{
    UIText *t = (UIText*)object;
    t->render(renderer);
}

void UIText::start()
{
    Engine::instance()->renderModule()->addHandler(this, _render);

    mTexture = new Texture(1, 1, new char[4] {(char)255, (char)255, (char)255, (char)255});

    mMaterial = new Material();
    mMaterial->setShader(Engine::instance()->defaultAssets()->fontShader());
    mMaterial->setTexture(mTexture);

    mMesh = new Mesh(new float[4 * 3], 4 * 3, new float[4 * 2], 4 * 2, new int[6] {
        0, 1, 3,
        0, 2, 3
    }, 6);
}

}
