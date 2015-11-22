//
// Created by Martin on 15. 11. 2015.
//

#ifndef POKEMON3D_MAINCHARACTER_H
#define POKEMON3D_MAINCHARACTER_H

#include "MovableCharacter.hpp"

class MainCharacter: public MovableCharacter {

private:

    float runSpeed = 20.0f;
    float turnSpeed = 160.0f;
    InputManager *inputManager;

    void checkInputs();

public:

    MainCharacter(GLint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                  float rotZ, float scale, InputManager *inputManager);
    MainCharacter(GLint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ,
                  float scale, float reflectivity, float shineDamper, InputManager *inputManager);
    void animate(Scene *scene, float delta) override;
};

#endif //POKEMON3D_MAINCHARACTER_H
