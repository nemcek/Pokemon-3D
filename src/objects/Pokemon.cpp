//
// Created by Martin on 30. 11. 2015.
//

#include <loaders/tiny_obj_loader.h>
#include "src/objects/Pokemon.hpp"
#include "Scene.hpp"

Pokemon::Pokemon(unsigned short id, LoaderPtr loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             InputManager *inputManager, const std::string &attack_obj_file, const std::string &attack_image_name,
                             bool canAttackAtStart)
        : MainCharacter(loader, object_name, file_name, position, rotX, rotY, rotZ, scale, inputManager) {

    this->id = id;
    this->attackObj = AttackPtr(new Attack(loader, attack_obj_file, attack_image_name, this->position, 0.0f, 0.0f, 0.0f, 0.05));
    this->canAttack = canAttackAtStart;
    this->startingPos = position;
}

Pokemon::Pokemon(unsigned short id, LoaderPtr loader, const std::string &object_name, const std::string &file_name,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             float reflectivity, float shineDamper, InputManager *inputManager,
                             const std::string &attack_obj_file, const std::string &attack_image_name,
                             bool canAttackAtStart)
        : MainCharacter(loader, object_name, file_name, position, rotX, rotY, rotZ, scale,
                           reflectivity, shineDamper, inputManager) {

    this->id = id;
    this->attackObj = AttackPtr(new Attack(loader, attack_obj_file, attack_image_name, this->position, 0.0f, 0.0f, 0.0f, 0.05));
    this->canAttack = canAttackAtStart;
    this->startingPos = position;
}

Pokemon::Pokemon(unsigned short id, LoaderPtr loader, MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ,
                 float scale, float reflectivity, float shineDamper, InputManager *inputManager,
                 const std::string &attack_obj_file, const std::string &attack_image_name, bool canAttackAtStart)
    : MainCharacter(loader, mesh, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper, inputManager) {
    this->id = id;
    this->attackObj = AttackPtr(new Attack(loader, attack_obj_file, attack_image_name, this->position, 0.0f, 0.0f, 0.0f, 0.05));
    this->canAttack = canAttackAtStart;
    this->startingPos = position;
}

SceneType Pokemon::animate(Scene &scene, float delta) {
    if (scene.sceneType == SceneType::BATTLE_SCEEN) {
        attackDelay += delta;

        if (attackDelay > 5.0f)
            canAttack = true;

        for (auto objectLoop : scene.objects) {
            if (objectLoop.get() == this)
                continue;

            auto att = std::dynamic_pointer_cast<Attack>(objectLoop);

            if (!att) {
                continue;
            }
            else {
                if (att->collisionDelay > 0.5f ) {
                    if (collidedWith(objectLoop)) {
                        objectLoop->needsDeletion = true;
                        attackDelay = 0.0f;
                        this->currentHp -= 1;

                        if (this->currentHp <= 0)
                            return SceneType::MAIN_SCEEN;

                        this->position.z += startingPos.z < 0.0f ? -att->knockbackForce : att->knockbackForce;
                    }
                }
            }
        }

        if (scene.isTPressed() && canAttack) {
            canAttack = false;
            attack(scene);
        }
    }

    if (scene.sceneType == SceneType::MAIN_SCEEN) {
        if (this->animation != nullptr) {
            this->animation->animate(delta);
            this->position = this->animation->position;
            this->rotX = this->animation->rotation.x;
            this->rotY = this->animation->rotation.y;
            this->rotZ = this->animation->rotation.z;
        }
    }

    createTransformationMatrix();
    return scene.sceneType;
}

void Pokemon::checkInputs() {
}

void Pokemon::attack(Scene &scene) {
    int count = (int)Math::random(1.0f, 10.0f);

    generateAttacks(count, scene);
}

void Pokemon::generateAttacks(int count, Scene &scene) {
//    this->attacks.clear();
    for (int i = 0; i < count; i++) {
        auto localAttack = AttackPtr(new Attack(attackObj, position, attackObj->rotX,
                                                attackObj->rotY, attackObj->rotZ, attackObj->scale,
                                                Math::random(3.0f, 4.0f), Math::random(0.0f, 180.0f)));

        localAttack->position.z = this->position.z - this->radius;
        localAttack->position.y = Math::random(this->center_point.Y_min * scale, this->center_point.Y_max * scale);
        localAttack->position.x = Math::random(this->center_point.X_min * scale, this->center_point.X_max * scale);

        scene.objects.push_back(localAttack);
    }

//    return attacks;
}
