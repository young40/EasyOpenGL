//
//  EasyOpenGL02.cpp
//  EasyOpenGL02
//
//  Created by Peter Young on 9/15/15.
//  Copyright © 2015 Peter Young. All rights reserved.
//

#include <iostream>
#include <cmath>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 04 -- 来个动态三角形");

    GLuint vertexShader   = EO_LoadShaderFromFile("VertexShader04.vs",   GL_VERTEX_SHADER);
    GLuint fragmentShader = EO_LoadShaderFromFile("FragmentShader04.fs", GL_FRAGMENT_SHADER);

    GLuint program = EO_CreateProgram(vertexShader, fragmentShader);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertexData[] = {
         0.0f,  0.7f, 0.0f,
        -0.7f, -0.7f, 0.0f,
         0.7f, -0.7f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    GLint aPosPositon = glGetAttribLocation(program, "aPos");
    glEnableVertexAttribArray(aPosPositon);
    glVertexAttribPointer(aPosPositon, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (std::sin(timeValue)/2) + 0.5;
        
        GLint uColorLocation = glGetUniformLocation(program, "uColor");
        glUniform4f(uColorLocation, 0.2, 0.0, greenValue, 1.0);

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
