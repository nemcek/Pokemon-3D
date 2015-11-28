//
// Created by Martin on 17. 11. 2015.
//

#include "src/objects/Light.hpp"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = position;
    this->color = color;
    this->attenuation = glm::vec3(1.0f, 0.0f, 0.0f);
}

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation) {
    this->position = position;
    this->color = color;
    this->attenuation = attenuation;
}
