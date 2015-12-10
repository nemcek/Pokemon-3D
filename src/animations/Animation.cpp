//
// Created by Martin on 7. 12. 2015.
//

#include "src/animations/Animation.hpp"

Animation::Animation(){

}

void Animation::init(){
    i = 0;
    animationTime = 0;
}

void Animation::add(KeyframePtr keyframe){
    keyframes.push_back(keyframe);
}

glm::vec3 Animation::lerp(glm::vec3 a, glm::vec3 b, float t){
    if(t > 1){
        t = 1;
    }

    return a * (1 - t) + b * t;
}

bool Animation::animate(float dt){
    if(i + 1 >= keyframes.size()){
        if (repeat)
            init();
        else
            return false;
    }

    float t = animationTime / (keyframes[i+1]->time - keyframes[i]->time);

    if (!keyframes[i]->useObjectsPosition)
        position = lerp(keyframes[i]->position, keyframes[i + 1]->position, t);

    rotation = lerp(keyframes[i]->rotation, keyframes[i + 1]->rotation, t);
    animationTime += dt;

    if(animationTime > (keyframes[i + 1]->time - keyframes[i]->time)+dt){
        i++;
        animationTime = 0;

        if (!keyframes[i]->useObjectsPosition)
            position = keyframes[i]->position;
    }

    return true;
}

Animation::~Animation(){}