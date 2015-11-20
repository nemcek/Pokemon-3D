//
// Created by Martin on 15. 11. 2015.
//

#include "src/objects/MainCharacter.h"

MainCharacter::MainCharacter(GLint program_id, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta,
                             InputManager *inputManager)
        : MovableCharacter(program_id, object_name, file_name, position, rotX, rotY, rotZ, scale, delta) {

    this->inputManager;
}

MainCharacter::MainCharacter(GLint program_id, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta,
                             float reflectivity, float shineDamper, InputManager *inputManager)
        : MovableCharacter(program_id, object_name, file_name, position, rotX, rotY, rotZ, scale, delta,
                           reflectivity, shineDamper) {

    this->inputManager = inputManager;
}

void MainCharacter::animate() {
    checkInputs();
    move();
    createTransformationMatrix();
}

glm::vec3 MainCharacter::getCenter() {
    return glm::vec3(this->texturedModel->matrix[3].x, this->center.y, this->texturedModel->matrix[3].z);
}

void MainCharacter::checkInputs() {
    if (inputManager->isWPressed()) {
        currentSpeed = runSpeed;
    } else if (inputManager->isSPressed()) {
        currentSpeed = -runSpeed;
    } else {
        currentSpeed = 0.0f;
    }

    if (inputManager->isAPressed()) {
        currentTurnSpeed = turnSpeed;
    }
    else if (inputManager->isDPressed()) {
        currentTurnSpeed = -turnSpeed;
    } else {
        currentTurnSpeed = 0.0f;
    }
}