//
// Created by Martin on 28. 11. 2015.
//

#include "src/objects/StreetLamp.hpp"

StreetLamp::StreetLamp(Loader *loader, glm::vec3 position)
        : Terrain(loader, "models/objects/StreetLamp.obj", "models/textures/StreetLamp.tga", position,
                 0.0f, 0.0f, 0.0f, 0.7f) {
    this->light = new Light(glm::vec3(position.x, position.y + 5.0f, position.z), glm::vec3(2.1f, 2.0f, 1.0f), glm::vec3(1.0f, 0.02f, 0.002f));
}
