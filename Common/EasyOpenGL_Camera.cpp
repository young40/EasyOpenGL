//
//  EasyOpenGL_Camera.cpp
//  EasyOpenGL
//
//  Created by Peter Young on 30/01/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include "EasyOpenGL.hpp"

EO_Camera::EO_Camera(vec3 position, vec3 up, float yaw, float pitch):
mFront(vec3(0.0f, 0.0f, -1.0f)),
mMovementSpeed(2.5f),
mMouseSensitivity(0.1f),
mZoom(45.0f)
{
    mPosition = position;
    mWorldUp  = up;
    mYaw      = yaw;
    mPitch    = pitch;

    mpPositionInit = mPosition;
    mpWorldUpInit  = mWorldUp;
    mpYawInit      = mYaw;
    mpPitchInit    = mPitch;
    mpZoomInit     = mZoom;

    updateCameraVectors();
}

EO_Camera::EO_Camera(float posX, float posY, float posZ,
                     float  upX, float  upY, float  upZ,
                     float yaw,  float pitch):
mFront(vec3(0.0f, 0.0f, -1.0f)),
mMovementSpeed(2.5f),
mMouseSensitivity(0.1f),
mZoom(45.0f)
{
    EO_Camera(vec3(posX, posY, posZ), vec3(upX, upY, upZ), yaw, pitch);
}

mat4 EO_Camera::getViewMatrix()
{
    return lookAt(mPosition, mPosition + mFront, mUp);
}

void EO_Camera::processKeyboard(Movement direction, float deltaTime)
{
    float velocity = mMovementSpeed * deltaTime;

    if (direction == Movement::kForward)
    {
        mPosition += mFront * velocity;
    }
    if (direction == Movement::kBackward)
    {
        mPosition -= mFront * velocity;
    }
    if (direction == Movement::kLeft)
    {
        mPosition -= mRight * velocity;
    }
    if (direction == Movement::kRight)
    {
        mPosition += mRight * velocity;
    }
}

void EO_Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw   += xoffset;
    mPitch += yoffset;

    if (constrainPitch)
    {
        mPitch = mPitch >  89.0f ?  89.0f : mPitch;
        mPitch = mPitch < -89.0f ? -89.0f : mPitch;
    }

    updateCameraVectors();
}

void EO_Camera::processScroll(float yoffset)
{
    mZoom -= yoffset;
    mZoom = (mZoom <= 1.0f)  ? 1.0f  : mZoom;
    mZoom = (mZoom >= 45.0f) ? 45.0f : mZoom;
}

void EO_Camera::updateCameraVectors()
{
    vec3 front;
    front.x = cos(radians(mYaw)) * cos(radians(mPitch));
    front.y = sin(radians(mPitch));
    front.z = sin(radians(mYaw)) * cos(radians(mPitch));

    mFront  = normalize(front);

    mRight = normalize(cross(mFront, mWorldUp));
    mUp    = normalize(cross(mRight, mFront));
}

void EO_Camera::stepFrame(GLFWwindow *window)
{
    float currentTime = glfwGetTime();
    mpDeltaTime = currentTime - mpLastTime;
    mpLastTime = currentTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        mpKeyPressingESC = true;
    }
    if (mpKeyPressingESC && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
    {
        mpKeyPressingESC = false;
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        mpKeyPressingR = true;
    }
    if (mpKeyPressingR && glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
    {
        mpKeyPressingR = false;

        resetCamera();
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        processKeyboard(Movement::kForward, mpDeltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        processKeyboard(Movement::kBackward, mpDeltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        processKeyboard(Movement::kLeft, mpDeltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        processKeyboard(Movement::kRight, mpDeltaTime);
    }
}

void EO_Camera::bindingWindow(GLFWwindow *window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, +[](GLFWwindow *window, double xpos, double ypos)
    {
        EO_Camera *camera = static_cast<EO_Camera*>(glfwGetWindowUserPointer(window));
        if (camera->mpIsFirstMouse)
        {
            camera->mpLastX = xpos;
            camera->mpLastY = ypos;
            camera->mpIsFirstMouse = false;
        }

        float xoffset = xpos - camera->mpLastX;
        float yoffset = ypos - camera->mpLastY;
        camera->mpLastX = xpos;
        camera->mpLastY = ypos;

        camera->processMouseMovement(xoffset, yoffset);
    });

    glfwSetScrollCallback(window, +[](GLFWwindow *window, double xoffset, double yoffset)
    {
        static_cast<EO_Camera*>(glfwGetWindowUserPointer(window))->processScroll(yoffset);
    });
}

void EO_Camera::resetCamera()
{
    mPosition = mpPositionInit;
    mWorldUp  = mpWorldUpInit;
    mYaw      = mpYawInit;
    mPitch    = mpPitchInit;
    mZoom     = mpZoomInit;

    updateCameraVectors();
}
