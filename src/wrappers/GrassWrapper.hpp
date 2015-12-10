//
// Created by Martin on 8. 12. 2015.
//

#ifndef POKEMON3D_GRASSWRAPPER_HPP
#define POKEMON3D_GRASSWRAPPER_HPP

#include "src/objects/Grass.hpp"
#include "src/animations/Animation.hpp"

class GrassWrapper {
private:
    GrassPtr mainGrass;
    AnimationPtr grassAnimation;
    LoaderPtr loader;

    void initGrassAnimation();
public:
    GrassWrapper(LoaderPtr loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
        float rotX, float rotY, float rotZ, float scale);
    GrassWrapper(LoaderPtr loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
        float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);

    void generateGrass(glm::vec2 bottomLeft, glm::vec2 topRight);

    std::vector<GrassPtr> grassParts;
};

typedef std::shared_ptr<GrassWrapper> GrassWrapperPtr;

#endif //POKEMON3D_GRASSWRAPPER_HPP
