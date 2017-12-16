#version 410

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 color;

out vec4 outColorFromVS;

void main()
{
    gl_Position = vec4(vert, 1.0f);
    
    outColorFromVS = vec4(color, 1.0f);
}
