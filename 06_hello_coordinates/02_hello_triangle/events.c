#include "events.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

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

void callback_frame_buffer_resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}