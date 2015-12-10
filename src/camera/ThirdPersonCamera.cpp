//
// Created by Martin on 16. 11. 2015.
//

#include "src/camera/ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(MovableCharacterPtr movableCharacter, GLFWwindow * window, InputManager *inputManager)
        : movableCharacter(movableCharacter){
    this->initPosition();
    this->inputManager = inputManager;

}

void ThirdPersonCamera::calculateZoom() {
    this->distance -= this->inputManager->getDistanceZoom();
}

void ThirdPersonCamera::calculatePitch() {
    if (this->inputManager->isRightMouseButtonPressed()) {
        float pitchChange = this->inputManager->getDistanceY();

        this->pitch -= pitchChange;

        if (this->pitch > 179.0f) {
            this->pitch = 179.0f;
        } else if (this->pitch < 1.0f) {
            this->pitch = 1.0f;
        }
    }
}

void ThirdPersonCamera::calculateAngle() {
    if (this->inputManager->isLeftMouseButtonPressed()) {
        float angleChanged = this->inputManager->getDistanceX();

        this->angle -= angleChanged;
    }
}

void ThirdPersonCamera::move() {
    calculateZoom();
    calculatePitch();
    calculateAngle();
    calculateZoom();

    float horDist = calculateHorizontalDistance();
    float vertDist = calculateVerticalDistance();

    calculateCameraPosition(horDist, vertDist);

    this->yaw = 180 - (*followTargetRotY + angle);
}

float ThirdPersonCamera::calculateHorizontalDistance() {
    return distance * glm::cos(glm::radians(this->pitch));
}

float ThirdPersonCamera::calculateVerticalDistance() {
    return distance * glm::sin(glm::radians(this->pitch));
}

void ThirdPersonCamera::calculateCameraPosition(float horizontalDistance, float verticalDistance) {
    float theta = *followTargetRotY + angle;
    float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
    float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));

//    position.x = movableCharacter->position.x - offsetX;
//    position.z = movableCharacter->position.z - offsetZ;
    position.x = followTargetPosition->x - offsetX;
    position.z = followTargetPosition->z - offsetZ;

//    position.y = movableCharacter->position.y + verticalDistance;
    position.y = followTargetPosition->y + verticalDistance;
}

glm::mat4 ThirdPersonCamera::getViewMatrix() {
    glm::mat4 viewMatrix;

    viewMatrix = glm::rotate(viewMatrix, glm::radians(this->pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(this->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-this->position.x, -this->position.y, -this->position.z));

    return  viewMatrix;
}

void ThirdPersonCamera::setFollowTarget(MovableCharacterPtr followTarget) {
    setFollowTarget(&followTarget->position, &followTarget->rotX, &followTarget->rotY, &followTarget->rotZ);
}

void ThirdPersonCamera::setFollowTarget(glm::vec3 *targetPositionVec, float *targetRotX, float *targetRotY, float *targetRotZ) {
    this->followTargetRotX = targetRotX;
    this->followTargetRotY = targetRotY;
    this->followTargetRotZ = targetRotZ;
    this->followTargetPosition = targetPositionVec;

    this->initPosition(*this->followTargetPosition);
}

void ThirdPersonCamera::initPosition() {
    initPosition(this->movableCharacter->position);
}

void ThirdPersonCamera::initPosition(glm::vec3 position) {
    this->pitch = 20.0f;
    this->angle = 0.0f;
    this->distance = 10.0f;
    this->position = position + glm::vec3(0.0f, this->pitch, this->distance);
}

void ThirdPersonCamera::setPosition(glm::vec3 position) {
    initPosition(position);
}
