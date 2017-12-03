//
//  EasyOpenGL_Shader.cpp
//  EasyOpenGL
//
//  Created by Peter Young on 03/12/2017.
//  Copyright © 2017 Peter Young. All rights reserved.
//

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "EasyOpenGL.hpp"

GLuint EO_LoadShaderFromFile(string file, GLuint shaderType)
{
    ifstream f;
    f.open(file);
    
    if (!f.is_open()) {
        cout << "打开文件失败:" << file << endl;
        return 0;
    }
    
    stringstream ss;
    ss << f.rdbuf();
    
    f.close();
    
    string shaderStr = ss.str();
    
    cout << "Got Shader:\n" << shaderStr << "\n" << endl;
    
    GLuint shader = glCreateShader(shaderType);
    
    if (shader == 0)
    {
        cout << "glCreateShader: create Shader failed" << endl;
        
        return 0;
    }
    
    const char* code = shaderStr.c_str();
    glShaderSource(shader, 1, (const GLchar**)&code, nullptr);
    
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE)
    {
        cout << "Shader compile failed:\n" << endl;
        
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
        
        glDeleteShader(shader);
        shader = 0;
        
        return 0;
    }
    
    return shader;
}

GLuint EO_CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    if (program == 0) {
        cout << "glCreateProgram: create program failed" << endl;
        return 0;
    }
    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    glLinkProgram(program);
    
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    
    if (status == GL_FALSE)
    {
        //TODO: 添加失败原因处理
        return 0;
    }
    
    return program;
}
