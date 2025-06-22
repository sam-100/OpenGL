#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "utils.h"
#include "events.h"
#include <iostream>
#include <math.h>
#include <vector>
#include "vertex.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

int screen_width = 800;
int screen_height = 600;

std::vector<vertex> vertices = {
    // position           // color              // texture
    {-0.5f, -0.5f,  0.0f,  0.2, 0.7, 0.1, 1.0,   0.0f, 0.0f},     // bottom-left
    {-0.5f,   0.5f, 0.0f,  0.2, 0.7, 0.1, 1.0,   0.0f, 1.0f},     // top-left
    { 0.5f,  0.5f,  0.0f,  0.2, 0.7, 0.1, 1.0,   1.0f, 1.0f},     // top-right
    { 0.5f, -0.5f,  0.0f,  0.2, 0.7, 0.1, 1.0,   1.0f, 0.0f}      // bottom-right
};

std::vector<GLuint> indices = {
    0, 1, 2, 
    2, 3, 0
};


int main(int argc, char **argv) {
    // Initialize glfw: Create a window, set callback functions, make current context
    GLFWwindow *window = glfw_init("1.5. Hello Transformations", 4, 2);
    
    // Initialize OpenGL: load opengl function pointers and create viewport
    opengl_init();

    // Create vertex array object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and load vertex buffer object
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Create and load element buffer object
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    
    // Generate and load the texture image
    GLuint texture_container = generate_texture("../resources/container.jpg");
    GLuint texture_face = generate_texture("../resources/awesomeface.png");

    
    // Link the Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(vertex), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), ((void*)(3*sizeof(float))));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(vertex), ((void*)(7*sizeof(float))));
    glEnableVertexAttribArray(2);
    
    
    // Compile and Link the shaders to create shader program
    GLuint program = compile_and_link_shader_program("src/vertex.glsl", "src/fragment.glsl");
    glUseProgram(program);

    shader_set_int(program, "texContainer", 0);
    shader_set_int(program, "texFace", 1);

    glm::mat4 transform(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.0f));
    transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));

    // rendering loop
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_container);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_face);
        
        glUseProgram(program);
        double time = glfwGetTime();
        float theta = (sin(time)+1.0f)/2.0f*3.14/1000.0f;
        transform = glm::rotate(transform, theta, glm::vec3(0.0f, 0.0f, 1.0f));
        shader_set_mat4(program, "transform", transform);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean-up resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

