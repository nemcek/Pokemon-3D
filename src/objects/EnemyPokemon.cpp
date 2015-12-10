//
// Created by Martin on 7. 12. 2015.
//

#include "src/objects/EnemyPokemon.hpp"
#include "Scene.hpp"

EnemyPokemon::EnemyPokemon(unsigned short id, LoaderPtr loader, const std::string & obj, const std::string & img,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity,
                             float shineDamper, InputManager *inputManager, const std::string &attack_obj_file,
                             const std::string &attack_image_name)
        : Pokemon(id, loader, obj, img, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper, inputManager,
                  attack_obj_file, attack_image_name, false) { }

EnemyPokemon::EnemyPokemon(unsigned short id, LoaderPtr loader, const std::string &obj, const std::string &img,
                             glm::vec3 position, float rotX, float rotY, float rotZ, float scale,
                             InputManager *inputManager, const std::string &attack_obj_file,
                             const std::string &attack_image_name)
        : Pokemon(id, loader, obj, img, position, rotX, rotY, rotZ, scale, inputManager,
                  attack_obj_file, attack_image_name, false) { }

EnemyPokemon::EnemyPokemon(unsigned short id, LoaderPtr loader, MeshPtr mesh, glm::vec3 position, float rotX,
                             float rotY, float rotZ, float scale, float reflectivity, float shineDamper,
                             InputManager *inputManager, const std::string &attack_obj_file,
                             const std::string &attack_image_name)
        : Pokemon(id, loader, mesh, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper, inputManager,
                  attack_obj_file, attack_image_name, false) { }

SceneType EnemyPokemon::animate(Scene &scene, float delta) {
    if (scene.sceneType == SceneType::BATTLE_SCEEN) {
        attackDelay += delta;

        if (wasAttacked && attackDelay > 3.0f || (!wasAttacked && attackDelay > 13.0f)) {
            // move back to starting position
            if (startingPos.z > this->position.z) {
                if (this->position.z + delta > startingPos.z)
                    this->position = startingPos;
                else
                    this->position.z += delta;

                return scene.sceneType;
            }

            canAttack = true;
        }

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
                        wasAttacked = true;
                        this->currentHp -= 1;
                        this->position.z -= att->knockbackForce;
                    }
                }
            }
        }

        if (canAttack) {
            canAttack = false;
            wasAttacked = false;
            attackDelay = 0.0f;
            attack(scene);
        }
    }

    createTransformationMatrix();

    if (this->currentHp <= 0)
        return SceneType::MAIN_SCEEN;

    return scene.sceneType;
}
