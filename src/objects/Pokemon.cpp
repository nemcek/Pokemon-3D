//
// Created by Martin on 30. 11. 2015.
//

#include <loaders/tiny_obj_loader.h>
#include "src/objects/Pokemon.hpp"
#include "Scene.hpp"

Pokemon::Pokemon(unsigned short id, Loader *loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             InputManager *inputManager, const std::string &attack_obj_file, const std::string &attack_image_name)
        : MainCharacter(loader, object_name, file_name, position, rotX, rotY, rotZ, scale, inputManager) {

    this->id = id;
    this->attackObj = new Attack(loader, attack_obj_file, attack_image_name, glm::vec3(0.0f), 0.0f, 0.0f, 0.0f, 0.05);
}

Pokemon::Pokemon(unsigned short id, Loader *loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             float reflectivity, float shineDamper, InputManager *inputManager,
                             const std::string &attack_obj_file, const std::string &attack_image_name)
        : MainCharacter(loader, object_name, file_name, position, rotX, rotY, rotZ, scale,
                           reflectivity, shineDamper, inputManager) {

    this->id = id;
    this->attackObj = new Attack(loader, attack_obj_file, attack_image_name, glm::vec3(0.0f), 0.0f, 0.0f, 0.0f, 0.05);
}

void Pokemon::animate(Scene *scene, float delta) {
//    checkInputs();
//    move(scene, delta);
    createTransformationMatrix();
}

void Pokemon::checkInputs() {
}

std::vector<Attack *> Pokemon::attack(Scene *scene) {
    int count = ((5 - 1) * (rand() / RAND_MAX)) + 1;

    return generateAttacks(4, objects);
}

std::vector<Attack *> Pokemon::generateAttacks(int count, Scene *scene) {
//    this->attacks.clear();
    for (int i = 0; i < count; i++) {
        Attack localAttack = *this->attackObj;
//        localAttack->position.z = -this->center_point.Z_max / this->scale;
//        localAttack->position.y = this->center_point.Y_min + ( std::rand() % (int)( this->center_point.Y_max - this->center_point.Y_min + 1 ) ) / this->scale;
//        localAttack->position.x = this->center_point.X_min + ( std::rand() % (int)( this->center_point.X_max - this->center_point.X_min + 1 ) ) / this->scale;
        localAttack.position.z = this->position.z;
        localAttack.position.y = ((0.5f - 0.0f) * ((float) rand() / (float) RAND_MAX)) + 0.0f;
        localAttack.position.x = ((0.5f - 0.0f) * ((float) rand() / (float) RAND_MAX)) + 0.0f;

        scene->objects.push_back(&localAttack);
    }

//    return attacks;
}
