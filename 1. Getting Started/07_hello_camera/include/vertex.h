#ifndef VERTEX_H
#define VERTEX_H

typedef struct position {
    float x, y, z;
} position;

typedef struct texture {
    float s, t;
} texture;

typedef struct vertex {
    position pos;
    texture tex;
} vertex;

#endif