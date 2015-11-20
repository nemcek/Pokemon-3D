//
// Created by Martin on 19. 11. 2015.
//

#include "src/objects/OtherCharacter.hpp"

OtherCharacter::OtherCharacter(GLint program_id, const std::string & obj_file, const std::string &image_file, glm::vec3 position, float rotX,
                               float rotY, float rotZ, float scale, float *delta)
                : MovableCharacter(program_id, obj_file, image_file, position, rotX, rotY, rotZ, scale, delta) {

}

OtherCharacter::OtherCharacter(GLint program_id, const std::string &obj_file, const std::string &image_file, glm::vec3 position, float rotX,
                               float rotY, float rotZ, float scale, float *delta, float reflectivity,
                               float shineDamper)
                : MovableCharacter(program_id, obj_file, image_file, position, rotX, rotY, rotZ, scale, delta, reflectivity,
                                    shineDamper) {

}

void OtherCharacter::animate() {
    generateMovement();
    move();
    createTransformationMatrix();
}

void OtherCharacter::generateMovement() {

    if (rand()) {
        int moveForward = rand() % 3;

        switch (moveForward) {
            case 0:
                currentSpeed = runSpeed;
                break;
            case 1:
//                currentSpeed = -runSpeed;
//                break;
            case 2:
                currentSpeed = 0.0f;
        }

        int rotate = rand() % 3;

        switch (rotate) {
            case 0:
                currentTurnSpeed = turnSpeed;
                break;
            case 1:
                currentTurnSpeed = -turnSpeed;
                break;
            case 2:
                currentTurnSpeed = 0.0f;
        }
    }

}