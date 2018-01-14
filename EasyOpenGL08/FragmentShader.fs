#version 410

in vec2 vertexTexCoord;

uniform sampler2D uniformTexture;

out vec4 fragmentColor;

void main()
{
    fragmentColor = texture(uniformTexture, vertexTexCoord);
}
