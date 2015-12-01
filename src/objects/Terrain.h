//
// Created by Martin on 14. 11. 2015.
//

#ifndef PPGSO_ENVIROMENT_H
#define PPGSO_ENVIROMENT_H

#include "src/objects/Mesh.h"

using namespace std;

class Terrain: public Mesh {
private:

public:
    Terrain(Loader *loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
                float rotX, float rotY, float rotZ, float scale);
    Terrain(Loader *loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
            float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);

    void animate(Scene *scene, float delta) override;
};

#endif //PPGSO_ENVIROMENT_H