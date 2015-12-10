//
// Created by Martin on 7. 12. 2015.
//

#include "src/animations/Keyframe.hpp"

Keyframe::Keyframe(float time, glm::vec3 rot) {
    this->time = time;
    rotation = rot;
    useObjectsPosition = true;
}

Keyframe::Keyframe(float t, glm::vec3 pos, glm::vec3 rot){
    time = t;
    position = pos;
    rotation = rot;
}

Keyframe::~Keyframe(){}