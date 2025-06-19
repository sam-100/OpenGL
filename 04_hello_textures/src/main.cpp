#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "events.h"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

const char *window_title = "Hello Textures";
int screen_width = 800;
int screen_height = 600;

float vertices[] = {
    // position           // color              // texture
    -0.5f, -0.5f,  0.0f,  0.2, 0.7, 0.1, 1.0,   0.0f, 0.0f,     // bottom-left
    -0.5f,   0.5f, 0.0f,  0.2, 0.7, 0.1, 1.0,   0.0f, 1.0f,     // top-left
     0.5f,  0.5f,  0.0f,  0.2, 0.7, 0.1, 1.0,   1.0f, 1.0f,     // top-right
     0.5f, -0.5f,  0.0f,  0.2, 0.7, 0.1, 1.0,   1.0f, 0.0f,     // bottom-right
};

unsigned int indices[] = {
    0, 1, 2, 
    2, 3, 0
};

int vertex_cnt = 4;

int main(int argc, char **argv) {
    // Initialize glfw
    if(glfwInit() == GLFW_FALSE)
        error("Failed to initialize glfw library.", -1);

    // create a window with opengl context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, window_title, NULL, NULL);
    if(!window) 
        error("Failed to create a window.", -1);

    // setting the callback functions
    glfwSetFramebufferSizeCallback(window, callback_frame_buffer_resize);
    glfwSetKeyCallback(window, callback_key_press_or_release);
    glfwSetWindowCloseCallback(window, callback_close_window);

    // set current context
    glfwMakeContextCurrent(window);

    // load all function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        error("Failed to load opengl function pointers.", -1);
    
    // set the viewport size
    glViewport(0, 0, screen_width, screen_height);

    // Create vertex array object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and load vertex buffer object
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    // Create and load element buffer object
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    // Generate and load the texture image
    GLuint texture_container = generate_texture("../resources/container.jpg");
    GLuint texture_face = generate_texture("../resources/awesomeface.png");

    
    // Link the Vertex Attributes
    int stride = sizeof(vertices)/vertex_cnt;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, stride, NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, stride, ((void*)(3*sizeof(float))));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, stride, ((void*)(7*sizeof(float))));
    glEnableVertexAttribArray(2);
    
    
    // Compile and Link the shaders to create shader program
    GLuint program = compile_and_link_shader_program("src/vertex.glsl", "src/fragment.glsl");
    glUseProgram(program);

    shader_set_int(program, "texContainer", 0);
    shader_set_int(program, "texFace", 1);

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
        shader_set_float(program, "colorFactor", (sin(time)+1.0f)/2.0f);

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

