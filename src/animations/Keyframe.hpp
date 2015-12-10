//
// Created by Martin on 7. 12. 2015.
//

#ifndef POKEMON3D_KEYFRAME_HPP
#define POKEMON3D_KEYFRAME_HPP

#include <memory>
#include <glm/glm.hpp>

class Keyframe {
public:
    Keyframe(float time, glm::vec3 rot);
    Keyframe(float time, glm::vec3 pos, glm::vec3 rot);

    ~Keyframe();

    glm::vec3 position;
    glm::vec3 rotation;
    float time;
    bool useObjectsPosition = false;
};

typedef std::shared_ptr<Keyframe> KeyframePtr;

#endif //POKEMON3D_KEYFRAME_HPP
