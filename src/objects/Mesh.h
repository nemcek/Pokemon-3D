#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "src/loaders/tiny_obj_loader.h"
#include "src/loaders/FileLoader.h"
#include "src/models/TexturedModel.hpp"
#include "src/extensions/Transformations.hpp"
#include "src/managers/InputManager.hpp"
#include "glm/ext.hpp"
#include "src/loaders/Loader.hpp"

class Scene;

typedef struct {
    float x;
    float y;
    float z;
} center_t;

class Mesh {

//    using namespace nsTexturedModel;

private:
    float calculateRadius();
    center_t calculateCenter();
    Loader *loader;

protected:

    virtual void initGeometry(const std::string &);
    virtual void initTexture(const std::string &);

public:

    GLuint program_id;

    glm::vec3 center;
    float rotY;
    float rotX;
    float rotZ;
    float scale;
    float radius;
    TexturedModel *texturedModel;

    Mesh(GLuint, const std::string &);
    Mesh(GLuint, Loader *loader, const std::string &, const std::string &);
    Mesh(GLuint, Loader *loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Mesh(GLuint, Loader *loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);
    virtual void render();
    virtual void animate(Scene *scene, float delta);
    glm::vec3 getCenter();
    glm::mat4 createTransformationMatrix();


    tinyobj::center_point_t center_point;
    glm::vec3 position;
};

#endif