#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <glad/glad.h>

void error(const char *msg, int error_code);

std::string load_file(const char *file_name);


/* --------------------------------------- Shader Related functions ------------------------------------ */
// loads and compiles the shader from given file and returns its openGL id
GLuint compile_shader(const char *file_name, GLenum shader_t);

// links vertex and fragment shaders provided to create a shader program and returns the program id
GLuint link_shaders(GLuint vs, GLuint fs);

// create a shader program 
GLuint compile_and_link_shader_program(const char *vertex_shader_file, const char *fragment_shader_file);

// Various functions to set uniform values in shader program
void shader_set_int(GLuint program, const char *name, int value);
void shader_set_bool(GLuint program, const char *name, bool value);
void shader_set_float(GLuint program, const char *name, float value);


/* --------------------------------------- Texture Related functions ------------------------------------- */
GLuint generate_texture(const char *file_name);


#endif