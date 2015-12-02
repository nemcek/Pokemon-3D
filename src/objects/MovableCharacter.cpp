//
// Created by Martin on 19. 11. 2015.
//

#include "src/objects/MovableCharacter.hpp"
#include "Scene.hpp"

MovableCharacter::MovableCharacter(LoaderPtr loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
        : Mesh(loader, object_name, file_name, position, rotX, rotY, rotZ, scale) {
}

MovableCharacter::MovableCharacter(LoaderPtr loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             float reflectivity, float shineDamper)
        : Mesh(loader, object_name, file_name, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper) {
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

void MovableCharacter::move(Scene *scene, float delta) {
    glm::vec3 prevRot = glm::vec3(rotX, rotY, rotZ);
    glm::vec3 prevPos = this->position;

    // rotate around Y axis
    increaseRotation(0.0f, currentTurnSpeed * delta, 0.0f);

    // calculate distance depending from rotation
    float distance = currentSpeed * delta;
    float dx = distance * glm::sin(glm::radians(rotY));
    float dz = distance * glm::cos(glm::radians(rotY));

    // move
    increasePosition(dx, 0.0f, dz);

    if (collided(scene)) {
        this->position = prevPos;
        this->rotX = prevRot.x;
        this->rotY = prevRot.y;
        this->rotZ = prevRot.z;

        return;
    }
}

bool MovableCharacter::collided(Scene *scene) {
    for (auto objectLoop : scene->objects) {
        if (objectLoop.get() == this)
            continue;

        if (collidedWith(objectLoop))
            return true;
    }

    for (auto wrapperLoop : scene->wrappers) {
        for (auto matrixLoop : wrapperLoop->matrixes) {
            if (collidedWith(matrixLoop, wrapperLoop->mesh->radius)) {
                return true;
            }
        }
    }

    return false;
}

bool MovableCharacter::collidedWith(MeshPtr mesh) {

    if (glm::distance(this->position, mesh->position) < this->radius + mesh->radius) {
        return true;
    }

    return false;
}

bool MovableCharacter::collidedWith(glm::mat4 matrix, float radius) {

    if (glm::distance(this->position, Transformations::getPosition(matrix)) < this->radius + (radius * Transformations::getScaleFactor(matrix))) {
        return true;
    }

    return false;
}