#version 410

in vec3 aPos;
in vec2 aTexCoord;

out vec2 vertexTexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    vertexTexCoord = aTexCoord;
}
