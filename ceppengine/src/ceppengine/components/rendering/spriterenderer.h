#pragma once

#include "../component.h"
#include "../../util/ref.h"
#include "../../util/color.h"
#include "../../assets/mesh.h"
#include "../../assets/material.h"
#include "../../assets/sprite.h"
#include "../../modules/rendermodule.h"

namespace cepp {

/**
 * Sprite renderer renders a sprite with a quad mesh.
 */
class SpriteRenderer : public Component
{
    public:
        SpriteRenderer();
        ~SpriteRenderer();

        virtual std::string typeName() const;

        Sprite *sprite() const;
        void setSprite(Sprite *sprite);

        Color color() const;
        void setColor(const Color &color);

        void render(IRenderer *renderer);

    protected:
        virtual void start();
        virtual void onDestroyed();

    private:
        void calculateVertices();
        void calculateTexCoords();

        Ref<Sprite> mSprite;

        Ref<Mesh> mMesh;
        Ref<Material> mMaterial;
        Color mColor;
};

} // namespace cepp
