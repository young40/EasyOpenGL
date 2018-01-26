//
//  main.cpp
//  EasyOpenGL11
//
//  Created by Shiling Yang on 26/01/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include <iostream>
#include "EasyOpenGL.hpp"

int main(int argc, const char * argv[]) {
    GLFWwindow *window = EO_CreateWindow(960, 640, "EasyOpenGL 11 颜色");
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
