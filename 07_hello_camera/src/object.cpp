#include "object.h"
#include "utils.h"
#include <iostream>


object::object(const std::vector<vertex> &vertices, GLuint shader_program) {
    for(vertex v : vertices)
        this->vertices.push_back(v);

    // Create vertex array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and load vertex buffer object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
    // Link the Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(vertex), ((void*)(0*sizeof(float))));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(vertex), ((void*)((sizeof(position)))));
    glEnableVertexAttribArray(1);
    
    // unbind vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Generate and load the texture image
    texture_container = generate_texture("../resources/container.jpg");
    texture_face = generate_texture("../resources/awesomeface.png");

    // Compile and Link the shaders to create shader program
    program = shader_program;
    glUseProgram(program);

    shader_set_int(program, "texContainer", 0);
    shader_set_int(program, "texFace", 1);

    model = glm::mat4(1.0f);
}

void object::draw(glm::mat4 view, glm::mat4 projection) const  {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = projection*view*model;
    draw(transform);
}

void object::draw(glm::mat4 transform) const {
    set_uniform_mat4("transform", transform);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_container);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_face);
    
    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void object::set_uniform_int(const char *name, int value) const {
    shader_set_int(program, name, value);
}

void object::set_uniform_float(const char *name, float value) const {
    shader_set_float(program, name, value);
}

void object::set_uniform_mat4(const char *name, glm::mat4 value) const {
    shader_set_mat4(program, name, value);
}


void object::translate(glm::vec3 displacement) {
    model = glm::translate(model, displacement);
}

void object::rotate(float angle, glm::vec3 axis) {
    model = glm::rotate(model, angle, axis);
}

void object::scale(glm::vec3 factor) {
    model = glm::scale(model, factor);
}

void object::set_model_matrix(glm::mat4 value) {
    model = value;
}

glm::mat4 object::get_model_matrix() const {
    return model;
}
