#version 410

in vec3 aPos;
in vec2 aTexCoord;

out vec2 vertexTexCoord;

uniform mat4 aModel;
uniform mat4 aView;
uniform mat4 aProjection;

void main()
{
    gl_Position = aProjection * aView * aModel * vec4(aPos, 1.0f);
    vertexTexCoord = aTexCoord;
}
