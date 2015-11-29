//
// Created by Martin on 29. 11. 2015.
//

#ifndef POKEMON3D_CAMERA_HPP
#define POKEMON3D_CAMERA_HPP

#include <glm/glm.hpp>

class Camera {

public:
    Camera();
    virtual glm::mat4 getViewMatrix() = 0;
    virtual void move() = 0;
};

#endif //POKEMON3D_CAMERA_HPP
