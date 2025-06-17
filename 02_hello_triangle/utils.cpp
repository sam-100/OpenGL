#include "utils.h"
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void error(const char *msg, int error_code) {
    cerr << "Error: " << msg << endl;
    const char *glfw_error_msg;
    glfwGetError(&glfw_error_msg);
    cerr << "glfw: " << glfw_error_msg << endl;
    exit(error_code);
}

string load_file(const char *file_name) {
    stringstream ss;

    ifstream in(file_name);

    if(in.is_open() == false) {
        cerr << "Error: Failed to open file " << file_name << endl;
        exit(1);
    }

    ss << in.rdbuf();
    in.close();
    
    return ss.str();
}


