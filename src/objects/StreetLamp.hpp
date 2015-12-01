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
    static LightPtr light;
//    Light *light;
    StreetLamp(Loader *loader, glm::vec3 position);

};

typedef std::shared_ptr<StreetLamp> StreetLampPtr;

#endif //POKEMON3D_STREETLAMP_HPP
