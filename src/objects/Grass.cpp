//
// Created by Martin on 8. 12. 2015.
//

#include "src/objects/Grass.hpp"
#include "Scene.hpp"

Grass::Grass(LoaderPtr loader, const std::string &object_name, const std::string &file_name, glm::vec3 position,
             float rotX, float rotY, float rotZ, float scale)
        : Terrain(loader, object_name, file_name, position, rotX, rotY, rotZ, scale) {
}

Grass::Grass(LoaderPtr loader, const std::string &object_name, const std::string &file_name, glm::vec3 position,
             float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper)
        : Terrain(loader, object_name, file_name, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper) {

}

Grass::Grass(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
        : Terrain(mesh, position, rotX, rotY, rotZ, scale){

}

Grass::Grass(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity,
             float shineDamper)
        : Terrain(mesh, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper){ }


SceneType Grass::animate(Scene &scene, float delta) {
    stepTime += delta;

    if (this->useAnimation) {
        if (!this->animation->animate(delta))
            isAnimating = false;
        else {
            this->rotX = this->animation->rotation.x;
            isAnimating = true;
        }
    }

    if (glm::distance(this->position, scene.mainCharacter->position) < this->radius + scene.mainCharacter->radius) {
//        if (stepTime > 3.0f) {
//            stepTime = 0.0f;
            int chance = (int) Math::random(0.0f, 100.0f);
            if (chance == 99)
                return SceneType::BATTLE_SCEEN;
//        }
    }

//    createTransformationMatrix();
    return scene.sceneType;
}

void Grass::initAnimation() {
    this->animation->init();
}