#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

void error(const char *msg, int error_code) {
    fprintf(stderr, "Error: %s\n", msg);
    const char *glfw_error_msg;
    glfwGetError(&glfw_error_msg);
    fprintf(stderr, "glfw: %s\n", glfw_error_msg);
    exit(error_code);
}

