//
//  EasyOpenGL12.cpp
//  EasyOpenGL12
//
//  Created by Peter Young on 04/02/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include <iostream>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "EasyOpenGL 12 -- 光照场景");

    vec3 cameraPos = vec3(0, 0, 3);
    vec3 cameraUp  = vec3(0, 1, 0);
    EO_Camera camera = EO_Camera(cameraPos, cameraUp);
    camera.bindingWindow(window);

    GLuint lightVertexShader = EO_LoadShaderFromFile("LightVertex12.vs", GL_VERTEX_SHADER);
    GLuint lightFragmentShader = EO_LoadShaderFromFile("LightFragment12.fs", GL_FRAGMENT_SHADER);
    GLuint lightProgram = EO_CreateProgram(lightVertexShader, lightFragmentShader);

    GLuint lampVertexShader = EO_LoadShaderFromFile("LampVertex12.vs", GL_VERTEX_SHADER);
    GLuint lampFragmentShader = EO_LoadShaderFromFile("LampFragment12.fs", GL_FRAGMENT_SHADER);
    GLuint lampProgram = EO_CreateProgram(lampVertexShader, lampFragmentShader);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    GLuint vbo, cubeVAO, ligthVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &ligthVAO);
    glBindVertexArray(ligthVAO);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        camera.stepFrame(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glUseProgram(lightProgram);
        glUniform3f(glGetUniformLocation(lightProgram, "objectColor"), 1.0f, 0.5f, 0.3f);
        glUniform3f(glGetUniformLocation(lightProgram, "lightColor"), 1.0f, 1.0f, 1.0f);

        mat4 projection = perspective(radians(camera.mZoom), 960.0f/640.0f, 0.1f, 100.0f);
        mat4 view = camera.getViewMatrix();
        mat4 model;

        glUniformMatrix4fv(glGetUniformLocation(lightProgram, "aProjection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightProgram, "aView"), 1, GL_FALSE, value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightProgram, "aModel"), 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glUseProgram(lampProgram);

        vec3 lampPos(1.2f, 1.0f, 2.0f);
        mat4 lampModel;
        lampModel = translate(lampModel, lampPos);
        lampModel = scale(lampModel, vec3(0.2f));

        glUniformMatrix4fv(glGetUniformLocation(lampProgram, "aProjection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampProgram, "aView"), 1, GL_FALSE, value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lampProgram, "aModel"), 1, GL_FALSE, value_ptr(lampModel));

        glBindVertexArray(ligthVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    return 0;
}
