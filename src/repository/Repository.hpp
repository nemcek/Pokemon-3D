//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_REPOSITORY_HPP
#define POKEMON3D_REPOSITORY_HPP

#include <glm/glm.hpp>

typedef struct PokemonData {
    unsigned short id;
    glm::vec3 rotation;
    glm::vec3 position;
    float scale;
};

class Repository {

public:
    Repository();

};

#endif //POKEMON3D_REPOSITORY_HPP
