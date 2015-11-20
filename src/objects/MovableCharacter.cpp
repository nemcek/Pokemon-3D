//
// Created by Martin on 19. 11. 2015.
//

#include "src/objects/MovableCharacter.hpp"

MovableCharacter::MovableCharacter(GLint program_id, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta)
        : Mesh(program_id, object_name, file_name, position, rotX, rotY, rotZ, scale) {

    this->delta = delta;
}

MovableCharacter::MovableCharacter(GLint program_id, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta,
                             float reflectivity, float shineDamper)
        : Mesh(program_id, object_name, file_name, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper) {

    this->delta = delta;
}

void MovableCharacter::increasePosition(float dX, float dY, float dZ) {
    this->position.x += dX;
    this->position.y += dY;
    this->position.z += dZ;
}

void MovableCharacter::increaseRotation(float rX, float rY, float rZ) {
    this->rotX += rX;
    this->rotY += rY;
    this->rotZ += rZ;
}

void MovableCharacter::move() {
    // rotate around Y axis
    increaseRotation(0.0f, currentTurnSpeed * (*delta), 0.0f);

    // calculate distance depending from rotation
    float distance = currentSpeed * (*delta);
    float dx = distance * glm::sin(glm::radians(rotY));
    float dz = distance * glm::cos(glm::radians(rotY));

    // move
    increasePosition(dx, 0.0f, dz);
}
