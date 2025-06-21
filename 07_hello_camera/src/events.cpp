#include "events.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"

extern glm::mat4 view, project;
extern camera cam;

void callback_close_window(GLFWwindow *window) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
} 

void callback_key_press_or_release(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const char *key_name = glfwGetKeyName(key, scancode);
    switch(key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

        // control keys
        case GLFW_KEY_LEFT:
            cam.translate(glm::vec3(-0.1, 0, 0));
            break;
        case GLFW_KEY_RIGHT:
            cam.translate(glm::vec3(0.1, 0, 0));
            break;
        case GLFW_KEY_UP:
            cam.translate(glm::vec3(0, 0.1, 0));
            break;
        case GLFW_KEY_DOWN:
            cam.translate(glm::vec3(0, -0.1, 0));
            break;
        case GLFW_KEY_W:
            cam.translate(glm::vec3(0, 0, -0.1));
            break;
        case GLFW_KEY_S:
            cam.translate(glm::vec3(0, 0, 0.1));
            break;
    }
}

void callback_frame_buffer_resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}