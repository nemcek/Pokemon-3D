//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_ATTACK_HPP
#define POKEMON3D_ATTACK_HPP

#include "src/objects/MovableCharacter.hpp"

class Attack : public MovableCharacter {

private:
    float movementSpeed = 0.1f;
    float rotateSpeed = 40.0f;

public:
    Attack(Loader *loader, const std::string &object_name, const std::string &file_name,
            glm::vec3 position, float rotX, float rotY, float rotZ, float scale);

    void move(Scene *scene, float delta);
    void animate(Scene *scene, float delta) override;
};

#endif //POKEMON3D_ATTACK_HPP
