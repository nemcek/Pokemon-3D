//
// Created by Martin on 16. 11. 2015.
//

#ifndef POKEMON3D_THIRDPERSONCAMERA_H
#define POKEMON3D_THIRDPERSONCAMERA_H

#include "src/objects/MainCharacter.h"
#include "src/managers/InputManager.hpp"
#include "src/camera/Camera.hpp"

class ThirdPersonCamera : public Camera {

private:

    glm::vec3 position;
    float pitch;
    float yaw;
    float distance;
    float angle;
    MovableCharacterPtr movableCharacter;
//    MovableCharacter *movableCharacter;
    InputManager *inputManager;

    void calculateZoom();
    void calculatePitch();
    void calculateAngle();
    float calculateHorizontalDistance();
    float calculateVerticalDistance();
    void calculateCameraPosition(float horizntalDistance, float verticalDistance);
    void initPosition();
    void initPosition(glm::vec3 position);
public:
    ThirdPersonCamera(MovableCharacterPtr movableCharacter, GLFWwindow * window, InputManager *inputManaget);
    void move() override;
    glm::mat4 getViewMatrix() override;
    void setFollowTarget(MovableCharacterPtr movableCharacter) override;
    void setPosition(glm::vec3 position) override;
};

typedef std::shared_ptr<ThirdPersonCamera> ThirdPersonCameraPtr;

#endif //POKEMON3D_THIRDPERSONCAMERA_H
