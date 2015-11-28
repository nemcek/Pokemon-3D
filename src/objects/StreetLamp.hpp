//
// Created by Martin on 28. 11. 2015.
//

#ifndef POKEMON3D_STREETLAMP_HPP
#define POKEMON3D_STREETLAMP_HPP

#include "src/objects/Terrain.h"
#include "src/objects/Light.hpp"
#include "src/loaders/Loader.hpp"

class StreetLamp : public Terrain {

public:
    Light *light;
    StreetLamp(GLint program_id, Loader *loader, glm::vec3 position);

};

#endif //POKEMON3D_STREETLAMP_HPP
