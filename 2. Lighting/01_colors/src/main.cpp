#include "glad/glad.h"
#include "GLFW/glfw3.h"
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
#include "camera.h"

float screen_width = 1000;
float screen_height = 800;

extern std::vector<vertex> vertices;
// extern std::vector<GLuint> indices;

camera cam(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 45.0f, screen_width/screen_height, 0.1f, 100.0f);


int main(int argc, char **argv) {
    // Initialize glfw: Create a window, set callback functions, make current context
    GLFWwindow *window = glfw_init("1.7. Hello Camera", 4, 2);
    
    // Initialize OpenGL: load opengl function pointers and create viewport
    opengl_init();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // capture the cursor

    // Create the cube objects
    GLuint program = compile_and_link_shader_program("src/vertex.glsl", "src/fragment.glsl");
    object cube(vertices, program);

    

    // rendering loop
    while(!glfwWindowShouldClose(window)) {
        // processInput();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean-up resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

