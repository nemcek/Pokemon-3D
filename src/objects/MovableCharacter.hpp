//
// Created by Martin on 19. 11. 2015.
//

#ifndef POKEMON3D_MOVABLECHARACTER_HPP
#define POKEMON3D_MOVABLECHARACTER_HPP

#include "src/objects/Mesh.h"
#include "src/managers/InputManager.hpp"
class MovableCharacter : public Mesh {
private:

    float *delta;

protected:

    float currentSpeed;
    float currentTurnSpeed;

    void move();
    void increasePosition(float dX, float dY, float dZ);
    void increaseRotation(float rX, float rY, float rZ);

public:

    MovableCharacter(GLint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                     float rotZ, float scale, float * delta);
    MovableCharacter(GLint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                     float rotZ, float scale, float * delta, float reflectivity, float shineDamper);

};

#endif //POKEMON3D_MOVABLECHARACTER_HPP
