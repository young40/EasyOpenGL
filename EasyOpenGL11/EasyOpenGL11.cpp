//
//  main.cpp
//  EasyOpenGL11
//
//  Created by Shiling Yang on 26/01/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include <iostream>
#include "EasyOpenGL.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xpos, double ypos);

vec3 cameraPos   = vec3(0.0f, 0.0f,  3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp    = vec3(0.0f, 1.0f,  0.0f);

float deltaTime =  0.0f;
float lastTime  =  0.0f;
float curFov    = 45.0f;

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "EasyOpenGL 10 -- 摄像机");

    GLuint vertexShaderID = EO_LoadShaderFromFile("VertexShader10.vs", GL_VERTEX_SHADER);
    GLuint fragmentShaderID = EO_LoadShaderFromFile("FragmentShader10.fs", GL_FRAGMENT_SHADER);
    GLuint programID = EO_CreateProgram(vertexShaderID, fragmentShaderID);

    GLfloat vertexData[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));

    glEnable(GL_DEPTH_TEST);

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

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    while (not glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        //        float raidus = 30.0f;
        //        float camX = sin(glfwGetTime()) * raidus;
        //        float camZ = cos(glfwGetTime()) * raidus;

        mat4 view;
        //        view = lookAt(vec3(camX, 0.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        view = lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

        for (int i=0; i<10; i++){
            mat4 projection;
            projection = perspective(radians(curFov), 960.0f/640.0f, 0.1f, 100.f);

            mat4 model;
            model = translate(model, cubePositions[i]);
            float angel = 20.0f*(i+1);
            model = rotate(model, (float)glfwGetTime() * radians(angel), vec3(1.0, 1.0, 1.0f));

            GLuint aModelID = glGetUniformLocation(programID, "aModel");
            GLuint aView = glGetUniformLocation(programID, "aView");
            GLuint aProjection = glGetUniformLocation(programID, "aProjection");

            glUniformMatrix4fv(aModelID, 1, GL_FALSE, value_ptr(model));
            glUniformMatrix4fv(aView, 1, GL_FALSE, value_ptr(view));
            glUniformMatrix4fv(aProjection, 1, GL_FALSE, value_ptr(projection));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

bool keyPressingR = false;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraFront*cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraFront*cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        keyPressingR = true;
    }
    if (keyPressingR && glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
    {
        cameraPos    = vec3(0.0f, 0.0f, 3.0f);
        cameraFront  = vec3(0.0f, 0.0f, -1.0f);
        keyPressingR = false;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

double lastX = 960.0/2.0;
double lastY = 640.0/2.0;

bool isFirstMouse = true;

float gyaw = -90.0;
float gpitch = 0;

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if(isFirstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    gyaw += xoffset;
    gpitch += yoffset;

    if (gpitch > 89)
    {
        gpitch = 89;
    }
    if (gpitch < -89)
    {
        gpitch = -89;
    }

    vec2 x(gyaw, gpitch);
    dump(x, 2);

    vec3 front;
    front.x = cos(radians(gyaw)) * cos(radians(gpitch));
    front.y = sin(radians(gpitch));
    front.z = sin(radians(gyaw)) * cos(radians(gpitch));

    //    dump(front);
    cameraFront = normalize(front);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (curFov >= 1.0f && curFov <= 45.0f)
    {
        curFov -= yoffset;
    }
    if (curFov < 1.0f)
    {
        curFov = 1.0f;
    }
    if (curFov > 45.0f)
    {
        curFov = 45.0f;
    }
}
