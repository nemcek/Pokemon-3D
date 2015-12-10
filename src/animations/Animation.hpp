//
// Created by Martin on 7. 12. 2015.
//

#ifndef POKEMON3D_ANIMATION_HPP
#define POKEMON3D_ANIMATION_HPP

#include <vector>
#include "src/animations/Keyframe.hpp"

class Animation {
public:
    Animation();

    ~Animation();

    void init();

    void add(KeyframePtr keyframe);

    glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t);

    bool animate(float dt);

    glm::vec3 position, rotation;
    float animationTime;
    int i;
    bool repeat = true;

    std::vector<KeyframePtr> keyframes;
};

typedef std::shared_ptr<Animation> AnimationPtr;

#endif //POKEMON3D_ANIMATION_HPP
