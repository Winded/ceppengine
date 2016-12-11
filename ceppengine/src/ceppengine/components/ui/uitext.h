#pragma once

#include "../component.h"
#include "../../assets/mesh.h"
#include "../../assets/material.h"
#include "../../modules/rendermodule.h"

namespace cepp {

class UIText : public Component
{
    public:
        UIText();
        ~UIText();

        virtual std::string typeName() const;

        std::string text() const;
        void setText(const std::string &text);

        Font *font() const;
        void setFont(Font * font);

        float fontSize() const;
        void setFontSize(float size);

        Color color() const;
        void setColor(const Color &color);

        void render(IRenderer *renderer);

    protected:
        virtual void start();

    private:
        std::string mText;
        Ref<Font> mFont;
        float mFontSize;

        Color mColor;

        Ref<Mesh> mMesh;
        Ref<Material> mMaterial;
        Ref<Texture> mTexture;
};

}
