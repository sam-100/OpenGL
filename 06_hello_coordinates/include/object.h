#ifndef OBJECT_H
#define OBJECT_H

#include "glad/glad.h"
#include "vertex.h"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

class object {
public:
    object(const std::vector<vertex> &vertices, const std::vector<GLuint> &indices, GLuint shader_program);
    
    void draw() const;
    
    void set_uniform_int(const char *name, int value);
    void set_uniform_float(const char *name, float value);
    void set_uniform_mat4(const char *name, glm::mat4 value);

private:
    std::vector<vertex> vertices;
    std::vector<GLuint> indices;
    GLuint VAO, VBO, EBO;
    GLuint program;
    GLuint texture_container, texture_face;
};

#endif