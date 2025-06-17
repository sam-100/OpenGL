#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "events.h"

int screen_width = 800;
int screen_height = 600;


int main(int argc, char **argv) {
    if(glfwInit() == GLFW_FALSE)
        error("Failed to initialize glfw library.", -1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "Hello Window (GLFW)", NULL, NULL);
    if(!window) 
        error("Failed to create a window.", -1);
    glfwMakeContextCurrent(window);

    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        error("Failed to load opengl function pointers.", -1);
    
    glViewport(0, 0, screen_width, screen_height);

    

    // setting the callback functions
    glfwSetFramebufferSizeCallback(window, callback_frame_buffer_resize);
    glfwSetKeyCallback(window, callback_key_press_or_release);
    glfwSetWindowCloseCallback(window, callback_close_window);

    while(!glfwWindowShouldClose(window)) {
        // processInput(window);

        glClearColor(0.0, 0.6, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

