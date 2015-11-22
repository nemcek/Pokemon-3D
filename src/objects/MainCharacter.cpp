//
// Created by Martin on 15. 11. 2015.
//

#include "src/objects/MainCharacter.h"

MainCharacter::MainCharacter(GLint program_id, Loader *loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             InputManager *inputManager)
        : MovableCharacter(program_id, loader, object_name, file_name, position, rotX, rotY, rotZ, scale) {

    this->inputManager;
}

MainCharacter::MainCharacter(GLint program_id, Loader *loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             float reflectivity, float shineDamper, InputManager *inputManager)
        : MovableCharacter(program_id, loader, object_name, file_name, position, rotX, rotY, rotZ, scale,
                           reflectivity, shineDamper) {

    this->inputManager = inputManager;
}

void MainCharacter::animate(Scene *scene, float delta) {
    checkInputs();
    move(scene, delta);
    createTransformationMatrix();
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