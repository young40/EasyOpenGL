#version 410

in vec4 outColorFromVS;

out vec4 outColor;

void main()
{
    outColor = outColorFromVS;
}
