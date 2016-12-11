#include "default.h"

namespace cepp {

DefaultAssets::DefaultAssets()
{
    mBasicShader = new Shader(
                "precision mediump float;                                                                     \
                attribute vec3 position;                                                                      \
                attribute vec2 uvCoordinates;                                                                 \
                                                                                                              \
                varying vec2 UV;                                                                              \
                                                                                                              \
                uniform mat4 WorldToViewportMatrix;                                                           \
                uniform mat4 LocalToWorldMatrix;                                                              \
                                                                                                              \
                void main()                                                                                   \
                {                                                                                             \
                    gl_Position = WorldToViewportMatrix * LocalToWorldMatrix * vec4(position.xyz, 1.0);       \
                    UV = uvCoordinates;                                                                       \
                }",
                "precision mediump float;                                                                     \
                varying vec2 UV;                                                                              \
                                                                                                              \
                uniform sampler2D Texture1;                                                                   \
                uniform vec4 BaseColor;                                                                       \
                                                                                                              \
                void main()                                                                                   \
                {                                                                                             \
                    gl_FragColor = texture2D(Texture1, UV) * BaseColor;                                       \
                }"
                );
    mFontShader = new Shader(
                "precision mediump float;"
                "attribute vec3 position;"
                "attribute vec2 uvCoordinates;"
                ""
                "varying vec2 UV;"
                ""
                "void main() {"
                  "gl_Position = vec4(position.xy, 0, 1);"
                  "UV = uvCoordinates;"
                "}",
                "precision mediump float;"
                "varying vec2 UV;"
                ""
                "uniform sampler2D Texture1;"
                "uniform vec4 BaseColor;"
                ""
                "void main() {"
                  "gl_FragColor = vec4(1, 1, 1, texture2D(Texture1, UV).a) * BaseColor;"
                "}"
                );
    mWhiteTexture = new Texture(1, 1, new char[4] {(char)255, (char)255, (char)255, (char)255});
    mQuadMesh = new Mesh(new float[4 * 3] {
        -0.5f, 0.5f, 0,
        0.5f, 0.5f, 0,
        0.5f, -0.5f, 0,
        -0.5f, -0.5f, 0
    }, 4 * 3, new float[4 * 2] {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    }, 4 * 2, new int[2 * 3] {
        0, 1, 3,
        1, 2, 3
    }, 6);
}

Shader *DefaultAssets::basicShader() const
{
    return mBasicShader;
}

Shader *DefaultAssets::fontShader() const
{
    return mFontShader;
}

Texture *DefaultAssets::whiteTexture() const
{
    return mWhiteTexture;
}

Mesh *DefaultAssets::quadMesh() const
{
    return mQuadMesh;
}

} // namespace cepp
