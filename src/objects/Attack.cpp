//
// Created by Martin on 30. 11. 2015.
//

#include "src/objects/Attack.hpp"

Attack::Attack(LoaderPtr loader, const std::string &object_name, const std::string &file_name, glm::vec3 position,
               float rotX, float rotY, float rotZ, float scale)
        : MovableCharacter(loader, object_name, file_name, position, rotX, rotY, rotZ, scale) {

}

void Attack::animate(Scene *scene, float delta) {
    move(scene, delta);
}

void Attack::move(Scene *scene, float delta) {
    this->position.z -= movementSpeed * delta;
    //this->rotZ += rotateSpeed *delta;

}