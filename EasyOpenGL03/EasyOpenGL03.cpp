//
//  main.cpp
//  EasyOpenGL03
//
//  Created by Peter Young on 03/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <iostream>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 03 -- 渐变色三角形");

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
