#version 410

layout (location = 0) in vec3 vert;

//out vec4 outColor;

void main()
{
    gl_Position = vec4(vert, 1);
    
 //   outColor = gl_Position;// vec4(0.2, 0.3, 0.5, 1.0);
}