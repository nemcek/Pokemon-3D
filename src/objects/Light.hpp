//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_LIGHT_H
#define POKEMON3D_LIGHT_H

#include <glm/glm.hpp>

class Light {

private:

public:
    glm::vec3 position;
    glm::vec3 color;

    Light(glm::vec3 position, glm::vec3 color);
};

#endif //POKEMON3D_LIGHT_H
