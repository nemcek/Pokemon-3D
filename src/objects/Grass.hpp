//
// Created by Martin on 8. 12. 2015.
//

#ifndef POKEMON3D_GRASS_HPP
#define POKEMON3D_GRASS_HPP

#include "src/objects/Terrain.h"
#include "src/animations/Animation.hpp"
#include "src/enums/Enums.hpp"

class Grass : public Terrain {

private:
    std::vector<std::shared_ptr<Grass>> grassParts;
    float stepTime = 0.0f;
public:
    Grass(LoaderPtr loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
        float rotX, float rotY, float rotZ, float scale);
    Grass(LoaderPtr loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
        float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);
    Grass(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Grass(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);
    SceneType animate(Scene &scene, float delta) override;
    void initAnimation();

    bool useAnimation;
    bool isAnimating = false;
    AnimationPtr animation;
};

typedef std::shared_ptr<Grass> GrassPtr;

#endif //POKEMON3D_GRASS_HPP
