//
// Created by Martin on 14. 11. 2015.
//

#include "src/objects/Terrain.h"

Terrain::Terrain(GLint program_id, Loader *loader, const std::string &object_name, const std::string &file_name,
                         glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
        : Mesh(program_id, loader, object_name, file_name, position, rotX, rotY, rotZ, scale) {
    createTransformationMatrix();
}

Terrain::Terrain(GLint program_id, Loader *loader, const std::string &object_name, const std::string &file_name,
                 glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity,
                 float shineDamper)
        : Mesh(program_id, loader, object_name, file_name, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper) {
    createTransformationMatrix();
}

void Terrain::animate(Scene *scene, float delta) {
    return;
}