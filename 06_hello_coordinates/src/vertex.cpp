#include "vertex.h"
#include <vector>
#include "glad/glad.h"

std::vector<vertex> vertices = {
    // position            // texture
    {-0.5f, -0.5f,  0.0f,  0.0f, 0.0f },     // bottom-left
    {-0.5f,   0.5f, 0.0f,  0.0f, 1.0f },     // top-left
    { 0.5f,  0.5f,  0.0f,  1.0f, 1.0f },     // top-right
    { 0.5f, -0.5f,  0.0f,  1.0f, 0.0f }      // bottom-right
};

std::vector<GLuint> indices = {
    0, 1, 2, 
    2, 3, 0
};
