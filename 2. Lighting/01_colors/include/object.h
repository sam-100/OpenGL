#ifndef OBJECT_H
#define OBJECT_H

#include "glad/glad.h"
#include "vertex.h"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

class object {
public:
    object(const std::vector<vertex> &vertices, GLuint shader_program);
    
    void draw(glm::mat4 view, glm::mat4 projection) const;
    void draw(glm::mat4 transform) const;
    
    void set_uniform_int(const char *name, int value) const ;
    void set_uniform_float(const char *name, float value) const ;
    void set_uniform_mat4(const char *name, glm::mat4 value) const ;

    void translate(glm::vec3 displacement);
    void rotate(float angle, glm::vec3 axis);
    void scale(glm::vec3 factor);

    void set_model_matrix(glm::mat4 value);
    glm::mat4 get_model_matrix() const;

private:
    std::vector<vertex> vertices;
    GLuint VAO, VBO;
    GLuint program;
    GLuint texture_container, texture_face;
    glm::mat4 model;
};

#endif