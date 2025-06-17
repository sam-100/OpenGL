#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <glad/glad.h>

void error(const char *msg, int error_code);

std::string load_file(const char *file_name);

GLuint compile_shader(const char *file_name, GLenum shader_t);
GLuint link_shaders(GLuint vs, GLuint fs);

#endif