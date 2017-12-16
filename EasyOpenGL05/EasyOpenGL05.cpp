//
//  main.cpp
//  EasyOpenGL05
//
//  Created by Peter Young on 16/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <iostream>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL -- 共用顶点的两个三角形");

    GLuint vertexShader   = EO_LoadShaderFromFile("VertexShader05.vs",   GL_VERTEX_SHADER);
    GLuint fragmentShader = EO_LoadShaderFromFile("FragmentShader05.fs", GL_FRAGMENT_SHADER);

    GLuint program = EO_CreateProgram(vertexShader, fragmentShader);

    GLfloat vertexData[] = {
         0.0f, -0.7f, 0.0f,     //1.0f, 0.0f, 0.0f, //左顶点及颜色(红)
         0.0f,  0.7f, 0.0f,     //0.0f, 1.0f, 0.0f, //右顶点及颜色(蓝)
         0.7f,  0.0f, 0.0f,     //0.0f, 0.0f, 1.0f, //上顶点及颜色(绿)
        -0.7f,  0.0f, 0.0f,     //0.6f, 0.6f, 0.6f, //下顶点及颜色(灰)
    };

    GLuint indexData[] = {
        0, 1, 2,                //1, 3, 5,
        0, 1, 3,                //3, 5, 7
    };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();

    return 0;
}
