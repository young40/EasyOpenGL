//
//  main.cpp
//  EasyOpenGL06
//
//  Created by Peter Young on 17/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "EasyOpenGL.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 06 -- 加装纹理");
    EO_CheckErro();

    GLuint vertexShader   = EO_LoadShaderFromFile("VertexShader06.vs",   GL_VERTEX_SHADER);
    GLuint fragmentShader = EO_LoadShaderFromFile("FragmentShader06.fs", GL_FRAGMENT_SHADER);
    GLuint program = EO_CreateProgram(vertexShader, fragmentShader);

    GLfloat vertexData[] = {
        -0.7f,  0.7f, 0.0f, //左上
        -0.7f, -0.7f, 0.0f, //左下
         0.7f, -0.7f, 0.0f, //右下
         0.7,   0.7f, 0.0f  //右上
    };

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint indexData[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    int width, height, channel;
    unsigned char *data = stbi_load("lena_std.jpg", &width, &height, &channel, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glBindVertexArray(vao);

//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        EO_CheckErro();

        glBindVertexArray(0);
        glUseProgram(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
