//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_ATTACK_HPP
#define POKEMON3D_ATTACK_HPP

#include "src/objects/MovableCharacter.hpp"
#include "src/enums/Enums.hpp"

class Pokemon;

class Attack : public MovableCharacter {

private:
    float movementSpeed = 3.33f;
    float rotateSpeed = 40.0f;
    float startingZpos;
public:
    float knockbackForce = 0.2f;
    float collisionDelay = 0.0f;

    Attack(LoaderPtr loader, const std::string &object_name, const std::string &file_name,
            glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Attack(TexturedModelPtr, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float movementSpeed, float rotationSpeed);
    Attack(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float movementSpeed, float rotationSpeed);
    SceneType move(Scene &scene, float delta);
    SceneType animate(Scene &scene, float delta) override;
};

typedef std::shared_ptr<Attack> AttackPtr;

#endif //POKEMON3D_ATTACK_HPP
