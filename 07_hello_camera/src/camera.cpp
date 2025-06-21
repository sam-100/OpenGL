#include "camera.h"

camera::camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far) {
    this->position = position;
    this->front = glm::normalize(target-position);
    this->up = up;
    this->right = glm::cross(front, up);
    projection = glm::perspective(glm::radians(fov), aspect, near, far);
}


void camera::translate(glm::vec3 displacement) {
    position += displacement;
}

glm::mat4 camera::get_transform(glm::mat4 model) const {
    return get_projection() * get_view() * model;
}

glm::mat4 camera::get_view() const {
    return glm::lookAt(position, position+front, up);
}
glm::mat4 camera::get_projection() const {
    return projection;
}

