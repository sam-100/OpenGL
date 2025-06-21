#include "events.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#include <iostream>

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
        case GLFW_KEY_A:
            cam.move_left();
            break;
        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            cam.move_right();
            break;
        case GLFW_KEY_UP:
            cam.move_up();
            break;
        case GLFW_KEY_DOWN:
            cam.move_down();
            break;
        case GLFW_KEY_W:
            cam.move_front();
            break;
        case GLFW_KEY_S:
            cam.move_back();
            break;
        case GLFW_KEY_SPACE:
            cam.reset();
            break;
    }
}

void callback_frame_buffer_resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void callback_cursor_pos(GLFWwindow *window, double xPos, double yPos) {
    static double x = xPos;
    static double y = yPos;

    double dx, dy;
    dx = xPos-x;
    dy = yPos-y;

    // todo: change camera yaw, and pitch here
    cam.rotate_horizontal(-dx);
    cam.rotate_vertical(-dy);

    x = xPos;
    y = yPos;
}

void callback_scroll(GLFWwindow *window, double xOffset, double yOffset) {
    cam.zoom(-yOffset);
}