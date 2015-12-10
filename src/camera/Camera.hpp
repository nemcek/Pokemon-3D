//
// Created by Martin on 29. 11. 2015.
//

#ifndef POKEMON3D_CAMERA_HPP
#define POKEMON3D_CAMERA_HPP

#include <glm/glm.hpp>
#include "src/objects/MovableCharacter.hpp"

class Camera {

public:
    Camera();
    virtual glm::mat4 getViewMatrix() = 0;
    virtual void move() = 0;
//    virtual void setFollowTarget(MovableCharacterPtr movableCharacter) = 0;
    virtual void setFollowTarget(glm::vec3 *targetPositionVec, float *targetRotX, float *targetRotY, float *targetRotZ) = 0;
    virtual void setFollowTarget(MovableCharacterPtr followTarget) = 0;
    virtual void setPosition(glm::vec3 position) = 0;
};

typedef std::shared_ptr<Camera> CameraPtr;

#endif //POKEMON3D_CAMERA_HPP
