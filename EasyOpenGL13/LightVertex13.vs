#version 410

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 aModel;
uniform mat4 aView;
uniform mat4 aProjection;

out vec3 fragNormal;
out vec3 fragPos;

void main()
{
    gl_Position = aProjection * aView * aModel * vec4(aPos, 1.0f);
    fragPos = vec3(aModel * vec4(aPos, 1.0f));
    fragNormal = aNormal;
}
