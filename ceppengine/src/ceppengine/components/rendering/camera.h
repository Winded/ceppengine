#pragma once

#include "../component.h"
#include "../../math/vector3.h"
#include "../../math/matrix4.h"
#include "../../util/color.h"

namespace cepp {

/**
 * The camera component turns the attached game object into the scene camera.
 * The scene is then rendered from the camera's point of view.
 */
class Camera : public Component
{
    public:
        Camera();

        virtual std::string typeName() const;

        float orthographicScale() const;
        void setOrthographicScale(float scale);

        Color backgroundColor() const;
        void setBackgroundColor(const Color &color);

        /**
         * Calculate orthographic projection matrix
         */
        Matrix4 projectionMatrix() const;

        /**
         * Calculate world to viewport matrix. This is basically projection matrix multiplied by world-to-local matrix.
         */
        Matrix4 worldToViewportMatrix();

        /**
         * Convert screen point to world position
         */
        Vector3 screenToWorldPosition(const Vector3 &pos);
        /**
         * Convert world position to screen point
         */
        Vector3 worldToScreenPosition(const Vector3 &pos);

    private:
        float mOrthographicScale;

        Color mBackgroundColor;

        // Caching the calculated view matrix saves us a lot of processing.
        bool mCacheValid;
        Vector3 mCachePosition, mCacheRotation, mCacheScreenRes;
        Matrix4 mCacheViewMatrix;
};

} // namespace cepp
