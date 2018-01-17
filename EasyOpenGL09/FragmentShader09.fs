#version 410

in vec3 vertexColor;

out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(vertexColor, 1.0f); //vec4(0.6, 0.6, 0.6, 1.0);
}
