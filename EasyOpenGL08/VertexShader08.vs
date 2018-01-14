#version 410

in vec3 aPos;
in vec2 aTexCoord;

uniform mat4 transform;

out vec2 vertexTexCoord;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    vertexTexCoord = aTexCoord;
}
