//
//  EasyOpenGL_Error.cpp
//  EasyOpenGL
//
//  Created by Peter Young on 17/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <stdio.h>

#include "EasyOpenGL.hpp"

GLenum _glCheckError(const char *file, int line){
    GLenum errorCode;

    while ( (errorCode = glGetError()) != GL_NO_ERROR) {
        string error;

        switch (errorCode) {
            case GL_INVALID_ENUM:                   error = "GL_INVALID_ENUM";                  break;
            case GL_INVALID_VALUE:                  error = "GL_INVALID_VALUE";                 break;
            case GL_INVALID_OPERATION:              error = "GL_INVALID_OPERATION";             break;
            case GL_OUT_OF_MEMORY:                  error = "GL_OUT_OF_MEMORY";                 break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
        }

        cout << "OpenGL Error: (" << errorCode << ")" << error << endl;
        cout << file << "(" << line << ")" << endl;
    }

    return errorCode;
}
