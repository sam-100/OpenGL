#include "camera.h"
#include <iostream>


camera::camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far) {
    this->position = position;
    this->front = glm::normalize(target-position);
    this->up = up;
    this->speed = 0.1f;
    this->sensitivity = 0.001f;
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
}


void camera::translate(glm::vec3 displacement) {
    position += displacement;
}

void camera::rotate_horizontal(float angle) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle*sensitivity, up);
    front = glm::normalize(glm::vec3(rotation * glm::vec4(front, 1)));
}

void camera::rotate_vertical(float angle) {
    glm::vec3 right = get_right();
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle * sensitivity, right);
    front = glm::normalize(glm::vec3(rotation * glm::vec4(front, 1)));
    up = glm::normalize(glm::vec3(rotation * glm::vec4(up, 1)));
}

void camera::zoom(float factor) {
    if(factor < 0 && fov <= 1) return;
    if(factor > 0 && fov >= 90) return;
    fov = fov+factor*sensitivity*10;
    // std::cout << "fov = " << fov << std::endl;
}

void camera::reset() {
    front = glm::vec3(0, 0, -1);
    position = glm::vec3(0, 0, 3);
    up = glm::vec3(0, 1, 0);
    fov = 45.0f;
}

glm::vec3 camera::get_right() const {
    return glm::normalize(glm::cross(front, up));
}

glm::mat4 camera::get_transform(glm::mat4 model) const {
    return get_projection() * get_view() * model;
}

glm::mat4 camera::get_view() const {
    return glm::lookAt(position, position+front, up);
}
glm::mat4 camera::get_projection() const {
    return glm::perspective(fov, aspect, near, far);
}


void camera::move_front() {
    position += front*speed;
}

void camera::move_back() {
    position -= front*speed;
}

void camera::move_left() {
    position -= get_right() * speed;
}

void camera::move_right() {
    position += get_right() * speed;
}

void camera::move_up() {
    position += up*speed;
}

void camera::move_down() {
    position -= up*speed;
}