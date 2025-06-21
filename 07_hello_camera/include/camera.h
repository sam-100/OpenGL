#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/matrix_transform.hpp"


class camera {
public:
    // camera();
    camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far);

    void translate(glm::vec3 displacement);

    glm::mat4 get_transform(glm::mat4 model) const;
    glm::mat4 get_view() const;
    glm::mat4 get_projection() const;


private:
    glm::vec3 position;
    glm::vec3 up, right, front;
    glm::mat4 projection;
};

#endif