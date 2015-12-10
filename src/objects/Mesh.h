#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

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
#include "src/extensions/Math.hpp"
#include "src/enums/Enums.hpp"

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

protected:
    LoaderPtr loader;

    virtual void initGeometry(const std::string &);
    virtual void initTexture(const std::string &);

public:

    glm::vec3 center;
    float rotY;
    float rotX;
    float rotZ;
    float scale;
    float radius;
    glm::vec3 position;
    TexturedModelPtr texturedModel;
    bool needsDeletion = false;

    Mesh(const std::string &);
    Mesh(TexturedModelPtr, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Mesh(std::shared_ptr<Mesh> mesh, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Mesh(LoaderPtr loader, const std::string &, const std::string &);
    Mesh(LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    Mesh(LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper);
    virtual void render();
    virtual SceneType animate(Scene &scene, float delta);
    glm::vec3 getCenter();
    glm::mat4 createTransformationMatrix();
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(float scale);

    tinyobj::center_point_t center_point;
};

typedef std::shared_ptr<Mesh> MeshPtr;

#endif