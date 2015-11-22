//
// Created by Martin on 19. 11. 2015.
//

#ifndef POKEMON3D_MOVABLECHARACTER_HPP
#define POKEMON3D_MOVABLECHARACTER_HPP

#include "src/objects/Mesh.h"

class MovableCharacter : public Mesh {
private:

    bool collided(Scene *scene);
    bool collidedWith(Mesh *mesh);
    bool collidedWith(glm::mat4 matrix, float radius);

protected:

    float currentSpeed;
    float currentTurnSpeed;

    void move(Scene *scene, float delta);
    void increasePosition(float dX, float dY, float dZ);
    void increaseRotation(float rX, float rY, float rZ);

public:

    MovableCharacter(GLint, Loader *loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                     float rotZ, float scale);
    MovableCharacter(GLint, Loader *loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                     float rotZ, float scale, float reflectivity, float shineDamper);

};

#endif //POKEMON3D_MOVABLECHARACTER_HPP
