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
// extern std::vector<GLuint> indices;

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

int main(int argc, char **argv) {
    // Initialize glfw: Create a window, set callback functions, make current context
    GLFWwindow *window = glfw_init("Hello Coordinates", 4, 2);
    
    // Initialize OpenGL: load opengl function pointers and create viewport
    opengl_init();

    // Create the cube objects
    GLuint program = compile_and_link_shader_program("src/vertex.glsl", "src/fragment.glsl");
    std::vector<object> cubes(10, object(vertices, program));
    
    // transformation matrices
    glm::mat4 view(1.0f), project(1.0f);
    for(int i=0; i<cubes.size(); i++) {
        object &cube = cubes[i];
        cube.translate(cubePositions[i]);
        cube.rotate(glm::radians(20.0f*i), glm::vec3(1.0f, 0.3f, 0.5f));
    }
    view = glm::translate(view, glm::vec3(0, 0, -3));
    project = glm::perspective(glm::radians(45.0f), screen_width/screen_height, 0.1f, 100.0f);
    

    // rendering loop
    while(!glfwWindowShouldClose(window)) {
        // processInput();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);

        for(object &cube : cubes) {            
            cube.draw(view, project);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean-up resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

