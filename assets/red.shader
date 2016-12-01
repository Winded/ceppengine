precision mediump float;
attribute vec3 position;
attribute vec2 uvCoordinates;

varying vec2 UV;

uniform mat4 WorldToViewportMatrix;
uniform mat4 LocalToWorldMatrix;

void main()
{
    gl_Position = WorldToViewportMatrix * LocalToWorldMatrix * vec4(position.xyz, 1.0);
    UV = uvCoordinates;
}
/*#SPLIT#*/
precision mediump float;
varying vec2 UV;

uniform sampler2D Texture1;
uniform vec4 BaseColor;

void main()
{
    gl_FragColor = vec4(1, 0, 0, 1);
}