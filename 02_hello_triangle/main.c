#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "events.h"

int screen_width = 800;
int screen_height = 600;

float vertices[] = {
    0.0f, 0.1f, 0.0f, 
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
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "Hello Window (GLFW)", NULL, NULL);
    if(!window) 
        error("Failed to create a window.", -1);

    // set current context
    glfwMakeContextCurrent(window);

    // load all function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        error("Failed to load opengl function pointers.", -1);
    
    // set the viewport size
    glViewport(0, 0, screen_width, screen_height);


    int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);


    // setting the callback functions
    glfwSetFramebufferSizeCallback(window, callback_frame_buffer_resize);
    glfwSetKeyCallback(window, callback_key_press_or_release);
    glfwSetWindowCloseCallback(window, callback_close_window);

    // rendering loop
    while(!glfwWindowShouldClose(window)) {
        // processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0.6, 0.1, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean-up resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

