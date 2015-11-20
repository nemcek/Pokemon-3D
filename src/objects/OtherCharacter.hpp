//
// Created by Martin on 19. 11. 2015.
//

#ifndef POKEMON3D_OTHERCHARACTER_HPP
#define POKEMON3D_OTHERCHARACTER_HPP

#include "src/objects/MovableCharacter.hpp"

class OtherCharacter : public MovableCharacter {

private:

    float runSpeed = 10.0;
    float turnSpeed = 160.0f;

    void generateMovement();

public:

    OtherCharacter(GLint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                    float rotZ, float scale, float * delta);
    OtherCharacter(GLint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                    float rotZ, float scale, float * delta, float reflectivity, float shineDamper);

    void animate() override;
};

#endif //POKEMON3D_OTHERCHARACTER_HPP
