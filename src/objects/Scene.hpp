//
// Created by Martin on 22. 11. 2015.
//

#ifndef POKEMON3D_SCENE_HPP
#define POKEMON3D_SCENE_HPP

#include "src/objects/Mesh.h"
#include "src/objects/Ground.hpp"
#include "src/engine/MasterRenderer.hpp"
#include "src/camera/ThirdPersonCamera.h"

class Scene {

private:
    std::vector<Mesh *> objects;
    std::vector<nsGround::Ground *> grounds;
    nsMaterRenderer::MasterRenderer *masterRenderer;
    Light *light;
    glm::mat4 projection;
    nsThirdPersonCamera::ThirdPersonCamera *camera;

public:
    Scene(nsMaterRenderer::MasterRenderer *masterRenderer, Light *light, glm::mat4 projection,
          nsThirdPersonCamera::ThirdPersonCamera *camera);
    void addObjectToScene(Mesh *mesh);
    void addGroundToScene(nsGround::Ground *ground);
    void animate(float delta);
    void render();

};

#endif //POKEMON3D_SCENE_HPP
