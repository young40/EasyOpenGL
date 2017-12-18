#version 410

in vec2 vertexTexCoord;

uniform sampler2D uniformTexture;

out vec4 fragColor;

void main()
{
    fragColor = texture(uniformTexture, vertexTexCoord);
}
