#include "camera.h"
#include "../../engine.h"

namespace cepp {

Camera::Camera() : mCacheValid(false), mOrthographicScale(5.f)
{

}

std::string Camera::typeName() const
{
    return "Camera";
}

float Camera::orthographicScale() const
{
    return mOrthographicScale;
}

Color Camera::backgroundColor() const
{
    return mBackgroundColor;
}

void Camera::setBackgroundColor(const Color &color)
{
    mBackgroundColor = color;
}

Matrix4 Camera::projectionMatrix() const
{
    Vector3 screen = Engine::instance()->runtimeModule()->screenResolution();
    Matrix4 m = Matrix4::identity;

    float aspectRatio = screen.x / screen.y;
    float width = mOrthographicScale * aspectRatio;
    float height = mOrthographicScale;

    float near = -0.1f;
    float far = -1000.f;
    float left = -width / 2.f;
    float right = width / 2.f;
    float bottom = -height / 2.f;
    float top = height / 2.f;

    float invRL = 1.f / (right -left);
    float invTB = 1.f / (top - bottom);
    float invFN = 1.f / (far - near);

    m.m11 = 2.f * invRL;
    m.m22 = 2.f * invTB;
    m.m33 = -2.f * invFN;

    m.m14 = -(right + left) * invRL;
    m.m24 = -(top + bottom) * invTB;
    m.m34 = -(far + near) * invFN;

    return m;
}

Matrix4 Camera::worldToViewportMatrix() const
{
    // Check if our cached view matrix is valid. If not, recalculate
    Vector3 pos = gameObject()->position();
    Vector3 rot = gameObject()->rotation();
    Vector3 screen = Engine::instance()->runtimeModule()->screenResolution();
    if(pos != mCachePosition || rot != mCacheRotation || screen != mCacheScreenRes) {
        mCachePosition = pos;
        mCacheRotation = rot;
        mCacheScreenRes = screen;
        mCacheValid = false;
    }

    if(mCacheValid) {
        return mCacheViewMatrix;
    }

    Matrix4 wToL = gameObject()->worldToLocalMatrix();
    Matrix4 proj = projectionMatrix();
    mCacheViewMatrix = proj * wToL;
    mCacheValid = true;
    return mCacheViewMatrix;
}

Vector3 Camera::screenToWorldPosition(const Vector3 &pos) const
{
    Vector3 screen = Engine::instance()->runtimeModule()->screenResolution();
    Vector3 sPos = pos;
    sPos.x = (sPos.x / screen.x) * 2.f - 1.f;
    sPos.y = (sPos.y / screen.y) * 2.f - 1.f;
    sPos.z = 0;

    Matrix4 worldMatrix = worldToViewportMatrix().invert();
    Matrix4 m = worldMatrix * sPos.toPositionMatrix();

    return Vector3::fromPositionMatrix(m);
}

Vector3 Camera::worldToScreenPosition(const Vector3 &pos) const
{
    Matrix4 screenMatrix = worldToViewportMatrix();
    Matrix4 m = screenMatrix * pos.toPositionMatrix();

    Vector3 screen = Engine::instance()->runtimeModule()->screenResolution();
    Vector3 sPos = Vector3::fromPositionMatrix(m);
    sPos.x = (sPos.x + 1.f) / 2.f * screen.x;
    sPos.y = (sPos.y + 1.f) / 2.f * screen.y;
    return sPos;
}

} // namespace cepp
