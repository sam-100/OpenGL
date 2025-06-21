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
#include "object.h"

float screen_width = 800;
float screen_height = 600;

extern std::vector<vertex> vertices;
extern std::vector<GLuint> indices;

int main(int argc, char **argv) {
    // Initialize glfw: Create a window, set callback functions, make current context
    GLFWwindow *window = glfw_init("Hello Transformations", 4, 2);
    
    // Initialize OpenGL: load opengl function pointers and create viewport
    opengl_init();

    GLuint program = compile_and_link_shader_program("src/vertex.glsl", "src/fragment.glsl");
    object cube(vertices, indices, program);

    
    // rendering loop
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);
        
        // time calculation 
        double time = glfwGetTime();
        float theta = (sin(time)+1.0f)/2.0f*360.0f/100.0f;
        
        // transform matrix 
        glm::mat4 model(1.0f), view(1.0f), project(1.0f);
        model = glm::rotate(model, theta, glm::vec3(1, 0, 0));
        view = glm::translate(view, glm::vec3(0, 0, -3));
        project = glm::perspective(glm::radians(45.0f), screen_width/screen_height, 0.1f, 100.0f);
        
        // draw cube
        glm::mat4 transform_mat = project*view*model;
        cube.set_uniform_mat4("transform", transform_mat);
        cube.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean-up resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

