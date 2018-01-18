//
//  main.cpp
//  EasyOpenGL08
//
//  Created by Peter Young on 14/01/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include <iostream>

#include "EasyOpenGL.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "EasyOpenGL 08 -- 来点运算");

    GLuint vertexShaderID = EO_LoadShaderFromFile("VertexShader08.vs", GL_VERTEX_SHADER);
    GLuint fragmentShaderID = EO_LoadShaderFromFile("fragmentShader08.fs", GL_FRAGMENT_SHADER);
    GLuint programID = EO_CreateProgram(vertexShaderID, fragmentShaderID);

    GLfloat vertexData[] = {
        // 位置                           纹理
        -0.7f,  0.7f, 0.0f,           0.0f, 1.0f, //左上
        -0.7f, -0.7f, 0.0f,           0.0f, 0.0f, //左下
         0.7f, -0.7f, 0.0f,           1.0f, 0.0f, //右下
         0.7,   0.7f, 0.0f,           1.0f, 1.0f, //右上
    };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));

    GLuint indexData[] = {
        0, 1, 2,
        0, 2, 3
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

    stbi_set_flip_vertically_on_load(true);
    int width, height, channel;
    unsigned char *data = stbi_load("lena_std.jpg", &width, &height, &channel, 0);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID);

    stbi_image_free(data);

    mat4 trans;
    trans = glm::translate(trans, vec3(0.3, 0.3, 0.0f));

    trans = scale(trans, vec3(0.5, 0.5, 0.5));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);

        mat4 trans2 = rotate(trans, (float)glfwGetTime(), vec3(0.0, 0.0f, 1.0f));

        GLuint transPos = glGetUniformLocation(programID, "transform");
        glUniformMatrix4fv(transPos, 1, GL_FALSE, value_ptr(trans2));

//        glBindVertexArray(vao);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
