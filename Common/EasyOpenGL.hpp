//
//  EasyOpenGL.hpp
//  EasyOpenGL
//
//  Created by Peter Young on 02/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#ifndef EasyOpenGL_hpp
#define EasyOpenGL_hpp

#include <stdio.h>

#include <string>
#include <iostream>

#include "EasyOpenGL.hpp"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

using namespace std;
using namespace glm;

void glfw_error_callback(int error, const char *desc);

GLFWwindow* EO_CreateWindow(int width, int height, std::string title);
GLuint EO_CreateProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint EO_LoadShaderFromFile(string file, GLuint shaderType);

GLenum _glCheckError(const char *file, int line);
#define EO_CheckErro() _glCheckError(__FILE__, __LINE__)

void dump(vec2 &v2, int len = 0);
void dump(vec3 &v3, int len = 0);
void dump(vec4 &v4, int len = 0);

void dump(mat2 &m2, int len = 0);
void dump(mat3 &m3, int len = 0);
void dump(mat4 &m4, int len = 0);

enum Movement
{
    kForward,
    kBackward,
    kLeft,
    kRight
};

class EO_Camera
{
public:
    vec3 mPosition;
    vec3 mFront;
    vec3 mUp;
    vec3 mRight;
    vec3 mWorldUp;

    float mYaw;
    float mPitch;

    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;

    EO_Camera(vec3  position = vec3(0.0f, 0.0f, 0.0f),
              vec3  up       = vec3(0.0f, 1.0f, 0.0f),
              float yaw      = -90.0f,
              float pitch    =   0.0f);

    EO_Camera(float posX, float posY, float posZ,
              float  upX, float  upY, float  upZ,
              float yaw, float pitch);

    mat4 getViewMatrix();

    void processKeyboard(Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processScroll(float yoffset);

    void stepFrame(GLFWwindow *window);
    void bindingWindow(GLFWwindow *window);

private:
    float mpLastTime;
    float mpDeltaTime;

    bool mpKeyPressingESC = false;
    bool mpKeyPressingR   = false;

    float mpLastX = 0;
    float mpLastY = 0;
    bool mpIsFirstMouse = true;

    vec3 mpPositionInit;
    vec3 mpFrontInit;
    vec3 mpUpInit;
    vec3 mpRightInit;
    vec3 mpWorldUpInit;

    float mpYawInit;
    float mpPitchInit;

    float mpMovementSpeedInit;
    float mpMouseSensitivityInit;
    float mpZoomInit;

    void updateCameraVectors();
    void resetCamera();
};

#endif /* EasyOpenGL_hpp */
