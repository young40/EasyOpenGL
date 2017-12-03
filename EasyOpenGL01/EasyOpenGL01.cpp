//
//  EasyOpenGL01.cpp
//  EasyOpenGL01
//
//  Created by Peter Young on 9/15/15.
//  Copyright © 2015 Peter Young. All rights reserved.
//

#include <iostream>
#include <GLFW/glfw3.h>

#include "EasyOpenGL.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 01");

    if (!window)
    {
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
