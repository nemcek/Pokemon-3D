//
// Created by Martin on 14. 11. 2015.
//

#ifndef PPGSO_ENVIROMENT_H
#define PPGSO_ENVIROMENT_H

#include <iostream>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/objects/Mesh.h"

using namespace std;

class Terrain: public Mesh {
private:

public:
    Terrain(GLint program_id, const std::string & object_name, const std::string & file_name, glm::vec3 position,
                float rotX, float rotY, float rotZ, float scale);
    Terrain(GLint program_id, const std::string & object_name, const std::string & file_name, glm::vec3 position,
            float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);

    void animate() override;
};

#endif //PPGSO_ENVIROMENT_H