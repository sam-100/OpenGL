#include "utils.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void error(const char *msg, int error_code) {
    cerr << "Error: " << msg << endl;
    const char *glfw_error_msg;
    glfwGetError(&glfw_error_msg);
    cerr << "glfw: " << glfw_error_msg << endl;
    exit(error_code);
}

string load_file(const char *file_name) {
    stringstream ss;

    ifstream in(file_name);

    if(in.is_open() == false) {
        cerr << "Error: Failed to open file " << file_name << endl;
        exit(1);
    }

    ss << in.rdbuf();
    in.close();
    
    return ss.str();
}


/* --------------------------------------- Shader Related functions ------------------------------------ */

GLuint compile_shader(const char *file_name, GLenum type) {
    int status;
    char infoLog[512];
    GLuint shader;

    string shader_str = load_file(file_name);
    const char *shader_src = shader_str.c_str();

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cerr << infoLog << endl;
        error("Failed to compile shader.", 2);
    }
    return shader;
}

GLuint link_shaders(GLuint VSO, GLuint FSO) {
    // Create and link shader program
    int status;
    char infoLog[512];
    GLuint program;
    
    program = glCreateProgram();
    glAttachShader(program, VSO);
    glAttachShader(program, FSO);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(!status) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        cerr << infoLog << endl;
        error("Failed to link the shader program.", 3);
    }
    return program;
}

GLuint compile_and_link_shader_program(const char *vertex_shader_file, const char *fragment_shader_file) {
    GLuint vso, fso, program;
    vso = compile_shader(vertex_shader_file, GL_VERTEX_SHADER);
    fso = compile_shader(fragment_shader_file, GL_FRAGMENT_SHADER);
    program = link_shaders(vso, fso);
    glDeleteShader(vso);
    glDeleteShader(fso);
    return program;
}

void shader_set_int(GLuint program, const char *name, int value) {
    GLint loc = glGetUniformLocation(program, name);
    glUniform1i(loc, value);
}

void shader_set_bool(GLuint program, const char *name, bool value) {
    GLint loc = glGetUniformLocation(program, name);
    glUniform1i(loc, (int)value);
}

void shader_set_float(GLuint program, const char *name, float value) {
    GLint loc = glGetUniformLocation(program, name);
    glUniform1f(loc, value);
}