//
// Created by Martin on 18. 11. 2015.
//

#ifndef POKEMON3D_MESHWRAPPER_H
#define POKEMON3D_MESHWRAPPER_H

#include "src/objects/Mesh.h"

class MeshWrapper {

private:
    GLuint programId;

    void createMatrixes(int count, glm::vec3 scale);
public:

    MeshPtr mesh;
//    Mesh *mesh;
    std::vector<glm::mat4> matrixes;

    MeshWrapper(LoaderPtr loader, const std::string &obj_file, const std::string &image_file, int count, glm::vec3 scale);
    MeshWrapper(LoaderPtr loader, const std::string &obj_file, const std::string &image_file, int count, glm::vec3 scale,
                float reflectivity, float shineDamper);

};

typedef std::shared_ptr<MeshWrapper> MeshWrapperPtr;

#endif //POKEMON3D_MESHWRAPPER_H
