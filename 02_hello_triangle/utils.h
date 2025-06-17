#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <glad/glad.h>

void error(const char *msg, int error_code);

std::string load_file(const char *file_name);

// loads and compiles the shader from given file and returns its openGL id
GLuint compile_shader(const char *file_name, GLenum shader_t);

// links vertex and fragment shaders provided to create a shader program and returns the program id
GLuint link_shaders(GLuint vs, GLuint fs);

#endif