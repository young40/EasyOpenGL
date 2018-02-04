#version 410

layout (location = 0) in vec3 aPos;

uniform mat4 aModel;
uniform mat4 aView;
uniform mat4 aProjection;

void main()
{
    gl_Position = aProjection * aView * aModel * vec4(aPos, 1.0f);
}
