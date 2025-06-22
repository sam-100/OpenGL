#ifndef EVENTS_H
#define EVENTS_H

#include <GLFW/glfw3.h>


void callback_close_window(GLFWwindow *window);
void callback_key_press_or_release(GLFWwindow *window, int key, int scancode, int action, int mods);
void callback_frame_buffer_resize(GLFWwindow *window, int width, int height);

#endif