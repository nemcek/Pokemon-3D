//
// Created by Martin on 15. 11. 2015.
//

#ifndef POKEMON3D_MAINCHARACTER_H
#define POKEMON3D_MAINCHARACTER_H

#include "src/objects/Mesh.h"
#include "glm/ext.hpp"
#include <GLFW/glfw3.h>


class MainCharacter: public Mesh {

private:

    int *keys;

    float runSpeed = 20.0f;
    float turnSpeed = 160.0f;
    float currentSpeed = 0.0f;
    float currenTurnSpeed = 0.0f;
    float* delta;

    void centerOnScreen();

public:

    MainCharacter(GLint, const std::string &, const std::string &, int *, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta);
    MainCharacter(GLint, const std::string &, const std::string &, int *, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float * delta,
                    float reflectivity, float shineDamper);
    void animate() override;
    glm::vec3 getCenter();
    void increasePosition(float dX, float dY, float dZ);
    void increaseRotation(float rX, float rY, float rZ);

};

#endif //POKEMON3D_MAINCHARACTER_H
