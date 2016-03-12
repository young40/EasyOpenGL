//
//  EasyOpenGL02.cpp
//  EasyOpenGL02
//
//  Created by Peter Young on 9/15/15.
//  Copyright © 2015 Peter Young. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

#include <OpenGL/gl3.h> //否则会找不到 glGenVertexArrays

#include <GLFW/glfw3.h>

using namespace std;

extern "C"
{
    static void glfw_error_callback(int error, const char *desc)
    {
        fprintf(stderr, "Running got error: %d,\t %s\n", error, desc);
    }
}

int loadShaderFromFile(string file, GLuint shaderType)
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

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
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


int main(int argc, const char * argv[]) {
    GLFWwindow *window;

    if (!glfwInit())
    {
        return -1;
    }

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 640, "轻轻松松OpenGL 02", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    cout << glGetString(GL_VENDOR) << endl;
    cout << glGetString(GL_RENDERER) << endl;
    cout << glGetString(GL_VERSION) << endl;

    GLuint vertexShader = loadShaderFromFile("VertexShader02.vs", GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShaderFromFile("FragmentShader02.fs", GL_FRAGMENT_SHADER);

    GLuint program = createProgram(vertexShader, fragmentShader);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertexData[] = {
        0.0f,  0.7f,  0.0f,
        -0.7f, -0.7f, 0.0f,
        0.7f,  -0.7f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(glGetAttribLocation(program, "vert"));
    glVertexAttribPointer(glGetAttribLocation(program, "vert"), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glBindVertexArray(vao);//TODO

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
