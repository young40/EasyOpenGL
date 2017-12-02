//
//  EasyOpenGL.cpp
//  EasyOpenGL
//
//  Created by Peter Young on 02/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <string>

#include "EasyOpenGL.hpp"

void glfw_error_callback(int error, const char *desc)
{
    fprintf(stderr, "Running got error: %d,\t %s\n", error, desc);
}

GLFWwindow* EO_CreateWindow(int width, int height, std::string title)
{
    GLFWwindow *window;
    
    if(!glfwInit())
    {
        return nullptr;
    }
    
    glfwSetErrorCallback(glfw_error_callback);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!window)
    {
        glfwTerminate();
        return nullptr;
    }
    
    glfwMakeContextCurrent(window);
    
    cout << "GL_VENDOR: \t"   << glGetString(GL_VENDOR)   << endl;
    cout << "GL_RENDERER: \t" << glGetString(GL_RENDERER) << endl;
    cout << "GL_VERSION: \t"  << glGetString(GL_VERSION)  << endl;
    
    return window;
}
