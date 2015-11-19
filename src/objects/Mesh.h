#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/loaders/tiny_obj_loader.h"
#include "src/loaders/FileLoader.h"
#include "src/models/TexturedModel.hpp"
#include "src/extensions/Transformations.hpp"

class TexturedModel;

class Mesh {

//    using namespace nsTexturedModel;

protected:

    virtual void initGeometry(const std::string &);
    virtual void initTexture(const std::string &);
    virtual glm::vec3 calculateCenter();

public:

    GLuint program_id;

    glm::vec3 center;
    float rotY;
    float rotX;
    float rotZ;
    float scale;
    TexturedModel *texturedModel;

    Mesh(GLuint, const std::string &);
    Mesh(GLuint, const std::string &, const std::string &);
    Mesh(GLuint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Mesh(GLuint, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);
    virtual void render();
    virtual void animate();
    glm::mat4 createTransformationMatrix();


    tinyobj::center_point_t center_point;
    glm::vec3 position;
};

#endif