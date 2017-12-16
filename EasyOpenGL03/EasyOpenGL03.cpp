//
//  main.cpp
//  EasyOpenGL03
//
//  Created by Peter Young on 03/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <iostream>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 03 -- 渐变色三角形");

    if (!window)
    {
        return 1;
    }

    GLuint vertexShader   = EO_LoadShaderFromFile("VertexShader03.vs",   GL_VERTEX_SHADER);
    GLuint fragmentShader = EO_LoadShaderFromFile("FragmentShader03.fs", GL_FRAGMENT_SHADER);

    GLuint program = EO_CreateProgram(vertexShader, fragmentShader);

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertexData[] = {
       0.0f,  0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
      -0.7f, -0.7f, 0.0f, 0.0f, 1.0f, 0.0f,
       0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    GLint aPosLocation = glGetAttribLocation(program, "aPos");
    glEnableVertexAttribArray(aPosLocation);
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);

    GLint aColorLocation = glGetAttribLocation(program, "aColor");
    glEnableVertexAttribArray(aColorLocation);
    glVertexAttribPointer(aColorLocation, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}
