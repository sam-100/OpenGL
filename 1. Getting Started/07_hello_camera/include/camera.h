#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/matrix_transform.hpp"


class camera {
public:
    // camera();
    camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far);

    void translate(glm::vec3 displacement);
    void rotate_horizontal(float angle_in_degrees);
    void rotate_vertical(float angle_in_degrees);
    void zoom(float factor);
    void reset();
    
    glm::vec3 get_right() const;
    glm::mat4 get_transform(glm::mat4 model) const;
    glm::mat4 get_view() const;
    glm::mat4 get_projection() const;

    void move_front();
    void move_back();
    void move_left();
    void move_right();
    void move_up();
    void move_down();


private:
    float sensitivity, speed;
    glm::vec3 position;
    glm::vec3 up, front;
    float fov, aspect, near, far;
};

#endif