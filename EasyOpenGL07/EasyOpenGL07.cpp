//
//  EasyOpenGL07.cpp
//  EasyOpenGL
//
//  Created by Peter Young on 11/01/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include <iostream>
#include <cstdlib>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 07 -- 多个VAO&VBO");

    GLuint vertexShaderID = EO_LoadShaderFromFile("VertexShader07.vs", GL_VERTEX_SHADER);
    GLuint fragmentShaderID = EO_LoadShaderFromFile("FragmentShader07.fs", GL_FRAGMENT_SHADER);
    GLuint programID = EO_CreateProgram(vertexShaderID, fragmentShaderID);

    GLfloat vertexData1[] = {
        // 位置
        -0.7f,  0.7f, 0.0f,
         0.7f,  0.7f, 0.0f,
         0.0f, -0.7f, 0.0f
    };

    GLfloat vertexData2[] = {
        // 位置
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    GLuint vaoIDs[2]; //声明vao Array
    GLuint vboIDs[2];

    glGenVertexArrays(2, vaoIDs);
    glGenBuffers(2, vboIDs);

    glBindVertexArray(vaoIDs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData1), vertexData1, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(vaoIDs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData2), vertexData2, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);

        glBindVertexArray(vaoIDs[rand()%2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}
