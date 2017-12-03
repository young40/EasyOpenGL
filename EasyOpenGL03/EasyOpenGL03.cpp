//
//  EasyOpenGL02.cpp
//  EasyOpenGL02
//
//  Created by Peter Young on 9/15/15.
//  Copyright © 2015 Peter Young. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include <OpenGL/gl3.h> //否则会找不到 glGenVertexArrays
#include <GLFW/glfw3.h>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 03 -- 来个动态三角形");

    GLint a;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &a);
    cout << "ssss" << a << endl;

    GLuint vertexShader = EO_LoadShaderFromFile("VertexShader03.vs", GL_VERTEX_SHADER);
    GLuint fragmentShader = EO_LoadShaderFromFile("FragmentShader03.fs", GL_FRAGMENT_SHADER);

    GLuint program = EO_CreateProgram(vertexShader, fragmentShader);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertexData[] = {
        0.0f,  0.7f,  0.0f,
        -0.7f, -0.7f, 0.0f,
        0.7f,  -0.7f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(glGetAttribLocation(program, "vert"));
    glVertexAttribPointer(glGetAttribLocation(program, "vert"), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (std::sin(timeValue)/2) + 0.5;
        
        GLint l = glGetUniformLocation(program, "outColor");
        glUniform4f(l, 0.2, 0.0, greenValue, 1.0);

        glBindVertexArray(vao);//TODO

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
