//
// Created by Martin on 30. 11. 2015.
//

#include "src/objects/Attack.hpp"
#include "Scene.hpp"

Attack::Attack(LoaderPtr loader, const std::string &object_name, const std::string &file_name, glm::vec3 position,
               float rotX, float rotY, float rotZ, float scale)
        : MovableCharacter(loader, object_name, file_name, position, rotX, rotY, rotZ, scale) {
    this->startingZpos = position.z;
}

Attack::Attack(TexturedModelPtr texturedModel, glm::vec3 position, float rotX, float rotY, float rotZ, float scale
        , float movementSpeed, float rotationSpeed)
        : MovableCharacter(texturedModel, position, rotX, rotY, rotZ, scale) {
    this->movementSpeed = movementSpeed;
    this->rotateSpeed = rotationSpeed;
    this->startingZpos = position.z;
}

Attack::Attack(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale
        , float movementSpeed, float rotationSpeed)
        : MovableCharacter(mesh, position, rotX, rotY, rotZ, scale) {
    this->movementSpeed = movementSpeed;
    this->rotateSpeed = rotationSpeed;
    this->startingZpos = position.z;
}

SceneType Attack::animate(Scene &scene, float delta) {
    return move(scene, delta);
}

SceneType Attack::move(Scene &scene, float delta) {
    collisionDelay += delta;

    if (position.z < -20.0f || position.z > 20.0f)
        this->needsDeletion = true;

    position.z += startingZpos > 0.0f ? -movementSpeed * delta : movementSpeed * delta;
    rotZ += rotateSpeed *delta;

    return scene.sceneType;
}