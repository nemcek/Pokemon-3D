//
// Created by Martin on 14. 11. 2015.
//

#include "src/objects/Terrain.h"
#include "Scene.hpp"

Terrain::Terrain(LoaderPtr loader, const std::string &object_name, const std::string &file_name,
                         glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
        : Mesh(loader, object_name, file_name, position, rotX, rotY, rotZ, scale) {
    createTransformationMatrix();
}

Terrain::Terrain(LoaderPtr loader, const std::string &object_name, const std::string &file_name,
                 glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity,
                 float shineDamper)
        : Mesh(loader, object_name, file_name, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper) {
    createTransformationMatrix();
}

Terrain::Terrain(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
        : Mesh (mesh, position, rotX, rotY, rotZ, scale) {

    createTransformationMatrix();
}

Terrain::Terrain(MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity,
                 float shineDamper)
        : Mesh (mesh, position, rotX, rotY, rotZ, scale) {

    this->texturedModel->texture->reflectivity = reflectivity;
    this->texturedModel->texture->shineDamper = shineDamper;
    createTransformationMatrix();
}

SceneType Terrain::animate(Scene &scene, float delta) {
    return scene.sceneType;
}