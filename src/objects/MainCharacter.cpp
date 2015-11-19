//
// Created by Martin on 15. 11. 2015.
//

#include "src/objects/MainCharacter.h"

MainCharacter::MainCharacter(GLint program_id, const std::string &object_name, const std::string &file_name, int *keys,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta)
        : Mesh(program_id, object_name, file_name, position, rotX, rotY, rotZ, scale) {

    this->keys = keys;
    this->delta = delta;
}

MainCharacter::MainCharacter(GLint program_id, const std::string &object_name, const std::string &file_name, int *keys,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta,
                             float reflectivity, float shineDamper)
        : Mesh(program_id, object_name, file_name, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper) {

    this->keys = keys;
    this->delta = delta;
}

void MainCharacter::centerOnScreen() {
    //this->translate(glm::vec3(- this->center.x, 0.0f, - this->center.z));
}

void MainCharacter::animate() {
    if (this->keys[GLFW_KEY_W]) {
        currentSpeed = runSpeed;
    } else if (this->keys[GLFW_KEY_S]) {
        currentSpeed = -runSpeed;
    } else {
        currentSpeed = 0.0f;
    }

    if (this->keys[GLFW_KEY_A]) {
        currenTurnSpeed = turnSpeed;
    }
    else if (this->keys[GLFW_KEY_D]) {
        currenTurnSpeed = -turnSpeed;
    } else {
        currenTurnSpeed = 0.0f;
    }


    increaseRotation(0.0f, currenTurnSpeed * (*delta), 0.0f);
    float distance = currentSpeed * (*delta);
    float dx = distance * glm::sin(glm::radians(rotY));
    float dz = distance * glm::cos(glm::radians(rotY));
    increasePosition(dx, 0.0f, dz);

    createTransformationMatrix();

    return;
}

glm::vec3 MainCharacter::getCenter() {
    return glm::vec3(this->texturedModel->matrix[3].x, this->center.y, this->texturedModel->matrix[3].z);
}

void MainCharacter::increasePosition(float dX, float dY, float dZ) {
    this->position.x += dX;
    this->position.y += dY;
    this->position.z += dZ;
}

void MainCharacter::increaseRotation(float rX, float rY, float rZ) {
    this->rotX += rX;
    this->rotY += rY;
    this->rotZ += rZ;
}