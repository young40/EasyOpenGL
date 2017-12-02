//
//  EasyOpenGL01.cpp
//  EasyOpenGL01
//
//  Created by Peter Young on 9/15/15.
//  Copyright © 2015 Peter Young. All rights reserved.
//

#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

extern "C"
{
    static void glfw_error_callback(int error, const char *desc)
    {
        fprintf(stderr, "Running got error: %d,\t %s\n", error, desc);
    }
}

int main(int argc, const char * argv[]) {
    GLFWwindow *window;

    if(!glfwInit())
    {
        return -1;
    }

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FLOATING, GL_TRUE);

    window = glfwCreateWindow(960, 640, "演示 01", nullptr, nullptr);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    cout << "GL_VENDOR: \t"   << glGetString(GL_VENDOR)   << endl;
    cout << "GL_RENDERER: \t" << glGetString(GL_RENDERER) << endl;
    cout << "GL_VERSION: \t"  << glGetString(GL_VERSION)  << endl;


    while (!glfwWindowShouldClose(window)) {
                glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
