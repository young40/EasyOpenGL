#version 410

uniform vec4 outColor;

out vec4 color22;

void main()
{
    color22 = outColor;// vec4(1.0, 0, 1.0, 1.0);
}