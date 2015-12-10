//
// Created by Martin on 14. 11. 2015.
//

#ifndef PPGSO_ENVIROMENT_H
#define PPGSO_ENVIROMENT_H

#include "src/objects/Mesh.h"
#include "src/enums/Enums.hpp"

using namespace std;

class Terrain: public Mesh {
private:

public:
    Terrain(LoaderPtr loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
                float rotX, float rotY, float rotZ, float scale);
    Terrain(LoaderPtr loader, const std::string & object_name, const std::string & file_name, glm::vec3 position,
            float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);
    Terrain(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Terrain(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);

    SceneType animate(Scene &scene, float delta) override;
};

typedef std::shared_ptr<Terrain> TerrainPtr;

#endif //PPGSO_ENVIROMENT_H