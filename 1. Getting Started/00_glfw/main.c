#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error(const char *msg, int error_code);
void callback_close_window(GLFWwindow *window);
void callback_key_press_or_release(GLFWwindow *window, int key, int scancode, int action, int mods);

int main(int argc, char **argv) {
    if(glfwInit() == GLFW_FALSE)
        error("Failed to initialize glfw library.", -1);

    GLFWwindow *window = glfwCreateWindow(900, 600, "1.0. Hello Window (GLFW)", NULL, NULL);
    if(!window) 
        error("Failed to create a window.", -1);

    // glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, callback_key_press_or_release);
    glfwSetWindowCloseCallback(window, callback_close_window);

    while(!glfwWindowShouldClose(window)) {
        glfwWaitEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void error(const char *msg, int error_code) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(error_code);
}

void callback_close_window(GLFWwindow *window) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void callback_key_press_or_release(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const char *key_name = glfwGetKeyName(key, scancode);
    if(action == GLFW_PRESS)
        printf("Key '%s' Pressed\n", key_name);
    else
        printf("Key '%s' Released\n", key_name);
    fflush(stdout);
    switch(key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
    }
}