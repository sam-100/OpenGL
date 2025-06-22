#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "events.h"
#include <iostream>

using namespace std;

int screen_width = 800;
int screen_height = 600;

float vertices[] = {
    0.0f, 0.6f, 0.0f, 
    -0.6f, -0.4f, 0.0f, 
    0.6f, -0.4f, 0.0f
};

int main(int argc, char **argv) {
    // Initialize glfw
    if(glfwInit() == GLFW_FALSE)
        error("Failed to initialize glfw library.", -1);

    // create a window with opengl context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "1.2. Hello Triangle", NULL, NULL);
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

    // Link the Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3*sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    GLuint VSO = compile_shader("vertex.glsl", GL_VERTEX_SHADER);
    GLuint FSO = compile_shader("fragment.glsl", GL_FRAGMENT_SHADER);
    GLuint program = link_shaders(VSO, FSO);

    // Bind the program
    glUseProgram(program);
    glDeleteShader(VSO);
    glDeleteShader(FSO);

    // rendering loop
    while(!glfwWindowShouldClose(window)) {
        // processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0.6, 0.1, 1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean-up resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

