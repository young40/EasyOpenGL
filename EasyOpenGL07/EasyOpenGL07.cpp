//
//  EasyOpenGL07.cpp
//  EasyOpenGL
//
//  Created by Peter Young on 11/01/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include <iostream>

#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "轻轻松松OpenGL 07 -- 来点运算");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }


    return 0;
}
