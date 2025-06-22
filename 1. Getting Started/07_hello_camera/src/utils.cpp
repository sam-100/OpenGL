#include "utils.h"
#include <stdlib.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "events.h"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

extern float screen_width, screen_height;

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

GLenum get_format(int channels) {
    if(channels == 3)
        return GL_RGB;
    if(channels == 4)
        return GL_RGBA;
    error("Unknown channel.", 5);
    return -1;
}

GLFWwindow *glfw_init(const char *title, int major_version, int minor_version) {
    // Initialize glfw
    if(glfwInit() == GLFW_FALSE)
        error("Failed to initialize glfw library.", -1);

    // create a window with opengl context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, title, NULL, NULL);
    if(!window) 
        error("Failed to create a window.", -1);

    // setting the callback functions
    glfwSetFramebufferSizeCallback(window, callback_frame_buffer_resize);
    glfwSetKeyCallback(window, callback_key_press_or_release);
    glfwSetWindowCloseCallback(window, callback_close_window);
    glfwSetCursorPosCallback(window, callback_cursor_pos);
    glfwSetScrollCallback(window, callback_scroll);

    // set current context
    glfwMakeContextCurrent(window);
    return window;
}

void opengl_init() {
    // load all function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        error("Failed to load opengl function pointers.", -1);

    // set the viewport size
    glViewport(0, 0, screen_width, screen_height);

    glEnable(GL_DEPTH_TEST);
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

void shader_set_mat4(GLuint program, const char *name, glm::mat4 value) {
    GLint loc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}


/* --------------------------------------- Texture Related functions ------------------------------------- */
GLuint generate_texture(const char *file_name) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(file_name, &width, &height, &nrChannels, 0);
    if(!data) 
        error("Failed to load image.", 4);
    
    GLenum format = get_format(nrChannels);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_set_flip_vertically_on_load(true);
    stbi_image_free(data);

    return texture;
}