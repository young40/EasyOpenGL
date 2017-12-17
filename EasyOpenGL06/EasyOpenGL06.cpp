//
//  main.cpp
//  EasyOpenGL06
//
//  Created by Peter Young on 17/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <iostream>
#include "EasyOpenGL.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 06 -- 加装纹理");

    GLuint vertexShader   = EO_LoadShaderFromFile("VertexShader06.vs",   GL_VERTEX_SHADER);
    GLuint fragmentShader = EO_LoadShaderFromFile("FragmentShader06.fs", GL_FRAGMENT_SHADER);
    GLuint program = EO_CreateProgram(vertexShader, fragmentShader);

    GLfloat vertexData[] = {
        0.0f, 0.7f, 0.0f,
        -0.7f, -0.7f, 0.0f,
        0.7f, -0.7f, 0.0f
    };

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    int width, height, channel;
    unsigned char *data = stbi_load("lena_std.jpg", &width, &height, &channel, 0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
