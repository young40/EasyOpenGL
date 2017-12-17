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

using namespace std;

void glfw_error_callback(int error, const char *desc);

GLFWwindow* EO_CreateWindow(int width, int height, std::string title);
GLuint EO_CreateProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint EO_LoadShaderFromFile(string file, GLuint shaderType);

#endif /* EasyOpenGL_hpp */
